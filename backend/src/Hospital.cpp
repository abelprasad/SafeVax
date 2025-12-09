#include "Hospital.h"
#include <algorithm>

Hospital::Hospital(int id, const std::string& name, int priority, int highRiskPop)
    : id(id), name(name), priority(priority), currentVaccines(0),
      requestedVaccines(0), highRiskPopulation(highRiskPop), waitTime(0.0) {}

void Hospital::setRequestedVaccines(int amount) {
    requestedVaccines = std::max(0, amount);
}

void Hospital::allocateVaccines(int amount) {
    currentVaccines += amount;
    requestedVaccines = std::max(0, requestedVaccines - amount);
}

void Hospital::updateWaitTime(double time) {
    waitTime += time;
}

bool Hospital::isStarved() const {
    // A hospital is considered starved if it has high need but long wait time
    return (requestedVaccines > 0) && (waitTime > 10.0);  // Threshold: 10 time units
}

double Hospital::calculateNeed() const {
    // Need based on high-risk population and current shortage
    double shortage = static_cast<double>(requestedVaccines - currentVaccines);
    double riskFactor = static_cast<double>(highRiskPopulation) / 1000.0;
    return shortage * riskFactor;
}
