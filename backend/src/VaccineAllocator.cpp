#include "VaccineAllocator.h"
#include <algorithm>
#include <numeric>

VaccineAllocator::VaccineAllocator(int totalVaccines)
    : totalVaccines(totalVaccines), availableVaccines(totalVaccines) {}

void VaccineAllocator::addHospital(std::shared_ptr<Hospital> hospital) {
    std::lock_guard<std::mutex> lock(allocationMutex);
    hospitals.push_back(hospital);
}

std::vector<std::shared_ptr<Hospital>> VaccineAllocator::getHospitals() const {
    return hospitals;
}

// First-Come-First-Served Algorithm
void VaccineAllocator::allocateFCFS() {
    std::lock_guard<std::mutex> lock(allocationMutex);

    for (auto& hospital : hospitals) {
        if (availableVaccines <= 0) break;

        int requested = hospital->getRequestedVaccines();
        int toAllocate = std::min(requested, availableVaccines);

        if (toAllocate > 0) {
            hospital->allocateVaccines(toAllocate);
            availableVaccines -= toAllocate;
        }
    }
}

// Priority-based Allocation
void VaccineAllocator::allocatePriority() {
    std::lock_guard<std::mutex> lock(allocationMutex);

    // Sort by priority (higher priority first)
    auto sortedHospitals = hospitals;
    std::sort(sortedHospitals.begin(), sortedHospitals.end(),
        [](const auto& a, const auto& b) {
            return a->getPriority() > b->getPriority();
        });

    for (auto& hospital : sortedHospitals) {
        if (availableVaccines <= 0) break;

        int requested = hospital->getRequestedVaccines();
        int toAllocate = std::min(requested, availableVaccines);

        if (toAllocate > 0) {
            hospital->allocateVaccines(toAllocate);
            availableVaccines -= toAllocate;
        }
    }
}

// Fair-share Allocation
void VaccineAllocator::allocateFairShare() {
    std::lock_guard<std::mutex> lock(allocationMutex);

    if (hospitals.empty()) return;

    // Calculate total demand
    int totalDemand = 0;
    for (const auto& hospital : hospitals) {
        totalDemand += hospital->getRequestedVaccines();
    }

    if (totalDemand == 0) return;

    // Allocate proportionally
    for (auto& hospital : hospitals) {
        int requested = hospital->getRequestedVaccines();
        if (requested > 0) {
            double proportion = static_cast<double>(requested) / totalDemand;
            int toAllocate = static_cast<int>(availableVaccines * proportion);
            toAllocate = std::min(toAllocate, requested);

            if (toAllocate > 0) {
                hospital->allocateVaccines(toAllocate);
                availableVaccines -= toAllocate;
            }
        }
    }
}

// Shortest Job First (smallest request first)
void VaccineAllocator::allocateSJF() {
    std::lock_guard<std::mutex> lock(allocationMutex);

    // Sort by requested amount (smallest first)
    auto sortedHospitals = hospitals;
    std::sort(sortedHospitals.begin(), sortedHospitals.end(),
        [](const auto& a, const auto& b) {
            return a->getRequestedVaccines() < b->getRequestedVaccines();
        });

    for (auto& hospital : sortedHospitals) {
        if (availableVaccines <= 0) break;

        int requested = hospital->getRequestedVaccines();
        int toAllocate = std::min(requested, availableVaccines);

        if (toAllocate > 0) {
            hospital->allocateVaccines(toAllocate);
            availableVaccines -= toAllocate;
        }
    }
}

void VaccineAllocator::replenishVaccines(int amount) {
    std::lock_guard<std::mutex> lock(allocationMutex);
    availableVaccines += amount;
    totalVaccines += amount;
}

bool VaccineAllocator::checkForStarvation() const {
    for (const auto& hospital : hospitals) {
        if (hospital->isStarved()) {
            return true;
        }
    }
    return false;
}

void VaccineAllocator::preventDeadlock() {
    // Ensure no hospital is starved by giving minimum allocation
    std::lock_guard<std::mutex> lock(allocationMutex);

    const int MINIMUM_ALLOCATION = 10;

    for (auto& hospital : hospitals) {
        if (hospital->isStarved() && availableVaccines >= MINIMUM_ALLOCATION) {
            hospital->allocateVaccines(MINIMUM_ALLOCATION);
            availableVaccines -= MINIMUM_ALLOCATION;
        }
    }
}
