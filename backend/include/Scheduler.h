#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "VaccineAllocator.h"
#include <queue>
#include <chrono>

/**
 * Scheduler for managing vaccine allocation requests
 * Implements OS concept: Process Scheduling
 */
class Scheduler {
private:
    VaccineAllocator& allocator;
    std::queue<int> requestQueue;  // Queue of hospital IDs (FCFS)

    // Scheduling metrics
    double totalWaitTime;
    int totalRequests;

public:
    explicit Scheduler(VaccineAllocator& allocator);

    // Request handling
    void addRequest(int hospitalId, int amount);
    void processRequests(VaccineAllocator::AllocationAlgorithm algorithm);

    // Metrics
    double getAverageWaitTime() const;
    double calculateThroughput() const;
    void resetMetrics();
};

#endif
