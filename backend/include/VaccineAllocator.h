#ifndef VACCINE_ALLOCATOR_H
#define VACCINE_ALLOCATOR_H

#include "Hospital.h"
#include <vector>
#include <mutex>
#include <memory>

/**
 * Manages vaccine resource allocation using OS scheduling algorithms
 * Implements OS concepts: Resource Allocation, Synchronization
 */
class VaccineAllocator {
private:
    int totalVaccines;
    int availableVaccines;
    std::vector<std::shared_ptr<Hospital>> hospitals;
    std::mutex allocationMutex;  // OS: Synchronization primitive

public:
    enum AllocationAlgorithm {
        FCFS,           // First-Come-First-Served
        PRIORITY,       // Priority-based scheduling
        FAIR_SHARE,     // Fair-share allocation
        SJF             // Shortest Job First (smallest request)
    };

    VaccineAllocator(int totalVaccines);

    // Hospital management
    void addHospital(std::shared_ptr<Hospital> hospital);
    std::vector<std::shared_ptr<Hospital>> getHospitals() const;

    // Allocation algorithms (OS: Scheduling algorithms)
    void allocateFCFS();
    void allocatePriority();
    void allocateFairShare();
    void allocateSJF();

    // Resource management
    void replenishVaccines(int amount);
    int getAvailableVaccines() const { return availableVaccines; }
    int getTotalVaccines() const { return totalVaccines; }

    // Deadlock prevention
    bool checkForStarvation() const;
    void preventDeadlock();
};

#endif
