#include "Scheduler.h"

Scheduler::Scheduler(VaccineAllocator& allocator)
    : allocator(allocator), totalWaitTime(0.0), totalRequests(0) {}

void Scheduler::addRequest(int hospitalId, int amount) {
    auto hospitals = allocator.getHospitals();

    for (auto& hospital : hospitals) {
        if (hospital->getId() == hospitalId) {
            hospital->setRequestedVaccines(amount);
            requestQueue.push(hospitalId);
            totalRequests++;
            break;
        }
    }
}

void Scheduler::processRequests(VaccineAllocator::AllocationAlgorithm algorithm) {
    // Update wait times for all hospitals with pending requests
    auto hospitals = allocator.getHospitals();
    for (auto& hospital : hospitals) {
        if (hospital->getRequestedVaccines() > 0) {
            hospital->updateWaitTime(1.0);  // Increment wait time
            totalWaitTime += 1.0;
        }
    }

    // Execute allocation based on chosen algorithm
    switch (algorithm) {
        case VaccineAllocator::FCFS:
            allocator.allocateFCFS();
            break;
        case VaccineAllocator::PRIORITY:
            allocator.allocatePriority();
            break;
        case VaccineAllocator::FAIR_SHARE:
            allocator.allocateFairShare();
            break;
        case VaccineAllocator::SJF:
            allocator.allocateSJF();
            break;
    }

    // Check for starvation and prevent deadlock
    if (allocator.checkForStarvation()) {
        allocator.preventDeadlock();
    }

    // Clear processed requests
    while (!requestQueue.empty()) {
        requestQueue.pop();
    }
}

double Scheduler::getAverageWaitTime() const {
    if (totalRequests == 0) return 0.0;
    return totalWaitTime / totalRequests;
}

double Scheduler::calculateThroughput() const {
    if (totalWaitTime == 0.0) return 0.0;
    return totalRequests / totalWaitTime;
}

void Scheduler::resetMetrics() {
    totalWaitTime = 0.0;
    totalRequests = 0;
}
