#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <string>
#include <vector>

/**
 * Represents a hospital as a "process" in the vaccine allocation system
 * Implements OS concept: Process representation
 */
class Hospital {
private:
    int id;
    std::string name;
    int priority;              // Priority level (OS: Priority Scheduling)
    int currentVaccines;       // Current vaccine inventory
    int requestedVaccines;     // Requested amount
    int highRiskPopulation;    // Number of high-risk individuals
    double waitTime;           // Wait time for allocation (OS: Scheduling metric)

public:
    Hospital(int id, const std::string& name, int priority, int highRiskPop);

    // Getters
    int getId() const { return id; }
    std::string getName() const { return name; }
    int getPriority() const { return priority; }
    int getCurrentVaccines() const { return currentVaccines; }
    int getRequestedVaccines() const { return requestedVaccines; }
    int getHighRiskPopulation() const { return highRiskPopulation; }
    double getWaitTime() const { return waitTime; }

    // Setters
    void setRequestedVaccines(int amount);
    void allocateVaccines(int amount);
    void updateWaitTime(double time);

    // OS Concepts
    bool isStarved() const;  // Deadlock prevention check
    double calculateNeed() const;  // Resource need calculation
};

#endif
