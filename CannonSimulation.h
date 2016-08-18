#pragma once

#include "Simulation.h"
#include "Cannon.h"
#include "Gravity.h"

class CannonSimulation : public Simulation<Cannon> {
private:
    double maxBoreLength; // meters
    double maxBoreWidth; // meters
    double maxGunPowderMass; // Kg
    double maxAngle; // degrees
    double maxPlatformHeight; // meters
    double targetDistance; // meters

    int totalGenerations;

    double gravity;

    Cannon createRandomIndividual() override;
    Cannon breed(Cannon cannon1, Cannon cannon2) override;
    void fitnessTest(Cannon &cannon) override;
    bool reachedGoal() override;
    void printPopulation() override;

    void mutate(Cannon &cannon) override;

    // TODO: write and implement this function
    double getMaximumHeight(Cannon cannon);
    double getFlightTime(Cannon cannon);
    double getDistanceShot(Cannon cannon);
    double getDistanceToTarget(Cannon cannon);
public:
    void simulate() override;
    CannonSimulation(int totalGenerations, int maxPopulation, int childrenPerGeneration, double targetDistance,
                     double maxBoreLength, double maxBoreWidth, double maxGunPowderMass, double maxAngle,
                     double maxPlatformHeight, double mutationChance, double gravity = Gravity::EARTH,
                     int printEveryNthGeneration = 10);
};