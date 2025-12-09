#include "httplib.h"
#include "Hospital.h"
#include "VaccineAllocator.h"
#include "Scheduler.h"
#include <memory>
#include <sstream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Global allocator and scheduler
VaccineAllocator allocator(10000);  // Start with 10,000 vaccines
Scheduler scheduler(allocator);

// Helper function to convert hospitals to JSON
json hospitalsToJson(const std::vector<std::shared_ptr<Hospital>>& hospitals) {
    json result;
    result["hospitals"] = json::array();

    for (const auto& h : hospitals) {
        json hospital;
        hospital["id"] = h->getId();
        hospital["name"] = h->getName();
        hospital["priority"] = h->getPriority();
        hospital["currentVaccines"] = h->getCurrentVaccines();
        hospital["requestedVaccines"] = h->getRequestedVaccines();
        hospital["highRiskPopulation"] = h->getHighRiskPopulation();
        hospital["waitTime"] = h->getWaitTime();
        hospital["need"] = h->calculateNeed();
        hospital["isStarved"] = h->isStarved();
        result["hospitals"].push_back(hospital);
    }

    return result;
}

int main() {
    std::cout << "Initializing VaxiShare server..." << std::endl;

    httplib::Server svr;

    std::cout << "Server object created" << std::endl;

    // Initialize some sample hospitals
    allocator.addHospital(std::make_shared<Hospital>(1, "City General Hospital", 3, 5000));
    allocator.addHospital(std::make_shared<Hospital>(2, "Community Health Center", 2, 2000));
    allocator.addHospital(std::make_shared<Hospital>(3, "Metropolitan Medical", 5, 8000));
    allocator.addHospital(std::make_shared<Hospital>(4, "Regional Hospital", 4, 6000));
    allocator.addHospital(std::make_shared<Hospital>(5, "Rural Clinic", 1, 1000));

    // ===== REST API ENDPOINTS =====

    // GET /api/status - Get overall system status
    svr.Get("/api/status", [](const httplib::Request&, httplib::Response& res) {
        json response;
        response["totalVaccines"] = allocator.getTotalVaccines();
        response["availableVaccines"] = allocator.getAvailableVaccines();
        response["averageWaitTime"] = scheduler.getAverageWaitTime();
        response["throughput"] = scheduler.calculateThroughput();
        response["hasStarvation"] = allocator.checkForStarvation();

        res.set_content(response.dump(), "application/json");
        res.set_header("Access-Control-Allow-Origin", "*");
    });

    // GET /api/hospitals - Get all hospitals
    svr.Get("/api/hospitals", [](const httplib::Request&, httplib::Response& res) {
        json response = hospitalsToJson(allocator.getHospitals());
        res.set_content(response.dump(), "application/json");
        res.set_header("Access-Control-Allow-Origin", "*");
    });

    // POST /api/request - Add vaccine request
    svr.Post("/api/request", [](const httplib::Request& req, httplib::Response& res) {
        try {
            json body = json::parse(req.body);
            int hospitalId = body["hospitalId"];
            int amount = body["amount"];

            scheduler.addRequest(hospitalId, amount);

            json response;
            response["success"] = true;
            response["message"] = "Request added successfully";

            res.set_content(response.dump(), "application/json");
            res.set_header("Access-Control-Allow-Origin", "*");
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"Invalid JSON\"}", "application/json");
        }
    });

    // POST /api/allocate - Process allocation with specified algorithm
    svr.Post("/api/allocate", [](const httplib::Request& req, httplib::Response& res) {
        try {
            json body = json::parse(req.body);
            std::string algorithm = body["algorithm"];
            VaccineAllocator::AllocationAlgorithm algo;

            if (algorithm == "FCFS") {
                algo = VaccineAllocator::FCFS;
            } else if (algorithm == "PRIORITY") {
                algo = VaccineAllocator::PRIORITY;
            } else if (algorithm == "FAIR_SHARE") {
                algo = VaccineAllocator::FAIR_SHARE;
            } else if (algorithm == "SJF") {
                algo = VaccineAllocator::SJF;
            } else {
                res.status = 400;
                res.set_content("{\"error\":\"Invalid algorithm\"}", "application/json");
                return;
            }

            scheduler.processRequests(algo);

            json response;
            response["success"] = true;
            response["message"] = "Allocation processed";
            response["hospitals"] = hospitalsToJson(allocator.getHospitals());

            res.set_content(response.dump(), "application/json");
            res.set_header("Access-Control-Allow-Origin", "*");
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"Invalid JSON\"}", "application/json");
        }
    });

    // POST /api/replenish - Add more vaccines to inventory
    svr.Post("/api/replenish", [](const httplib::Request& req, httplib::Response& res) {
        try {
            json body = json::parse(req.body);
            int amount = body["amount"];
            allocator.replenishVaccines(amount);

            json response;
            response["success"] = true;
            response["totalVaccines"] = allocator.getTotalVaccines();
            response["availableVaccines"] = allocator.getAvailableVaccines();

            res.set_content(response.dump(), "application/json");
            res.set_header("Access-Control-Allow-Origin", "*");
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"Invalid JSON\"}", "application/json");
        }
    });

    // POST /api/hospital - Add a new hospital
    svr.Post("/api/hospital", [](const httplib::Request& req, httplib::Response& res) {
        try {
            json body = json::parse(req.body);
            int id = body["id"];
            std::string name = body["name"];
            int priority = body["priority"];
            int highRiskPop = body["highRiskPopulation"];

            auto hospital = std::make_shared<Hospital>(id, name, priority, highRiskPop);
            allocator.addHospital(hospital);

            json response;
            response["success"] = true;
            response["message"] = "Hospital added";

            res.set_content(response.dump(), "application/json");
            res.set_header("Access-Control-Allow-Origin", "*");
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"Invalid JSON\"}", "application/json");
        }
    });

    // GET /api/metrics - Get scheduling metrics
    svr.Get("/api/metrics", [](const httplib::Request&, httplib::Response& res) {
        json response;
        response["averageWaitTime"] = scheduler.getAverageWaitTime();
        response["throughput"] = scheduler.calculateThroughput();

        res.set_content(response.dump(), "application/json");
        res.set_header("Access-Control-Allow-Origin", "*");
    });

    // Serve static files from frontend directory
    svr.Get("/", [](const httplib::Request&, httplib::Response& res) {
        std::ifstream file("../frontend/index.html");
        if (file) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            res.set_content(buffer.str(), "text/html");
        } else {
            res.status = 404;
            res.set_content("Frontend not found", "text/plain");
        }
    });

    // Serve CSS files
    svr.Get("/css/style.css", [](const httplib::Request&, httplib::Response& res) {
        std::ifstream file("../frontend/css/style.css");
        if (file) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            res.set_content(buffer.str(), "text/css");
        }
    });

    // Serve JS files
    svr.Get("/js/app.js", [](const httplib::Request&, httplib::Response& res) {
        std::ifstream file("../frontend/js/app.js");
        if (file) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            res.set_content(buffer.str(), "application/javascript");
        }
    });

    // Handle OPTIONS for CORS preflight
    svr.Options(".*", [](const httplib::Request&, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
    });

    // Start server
    std::cout << "VaxiShare Backend Server Starting..." << std::endl;
    std::cout << "Server running on http://localhost:8080" << std::endl;
    std::cout << "API Documentation:" << std::endl;
    std::cout << "  GET  /api/status      - System status" << std::endl;
    std::cout << "  GET  /api/hospitals   - List all hospitals" << std::endl;
    std::cout << "  POST /api/request     - Add vaccine request" << std::endl;
    std::cout << "  POST /api/allocate    - Process allocation" << std::endl;
    std::cout << "  POST /api/replenish   - Replenish vaccines" << std::endl;
    std::cout << "  POST /api/hospital    - Add new hospital" << std::endl;
    std::cout << "  GET  /api/metrics     - Scheduling metrics" << std::endl;
    std::cout << "\nStarting server on port 8080..." << std::endl;

    if (!svr.listen("0.0.0.0", 8080)) {
        std::cerr << "ERROR: Failed to start server on port 8080" << std::endl;
        std::cerr << "Make sure the port is not already in use." << std::endl;
        return 1;
    }

    return 0;
}
