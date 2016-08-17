#pragma once

#include "Simulation.h"
#include "Cannon.h"

class CannonSimulation : public Simulation<Cannon> {
private:
    Cannon createRandomIndividual() override;
    Cannon breed(Cannon cannon1, Cannon cannon2) override;

    void fitnessTest(Cannon &cannon) override;
    bool reachedGoal() override;

    void testPopulation() override;
    void printPopulation() override;

    void mutate(Cannon &cannon) override;
    double mutateDouble(double value, double percentageChance, double maxValue);
    // TODO: choose a better name for this function
    double randomDoubleBetweenDataMembers(double value1, double value2);

    // TODO: choose a better name for this function
    void haveChildren();

    // TODO: write and implement this function
    double getMaximumHeight(Cannon cannon);
    double getFlightTime(Cannon cannon);
    double getDistanceShot(Cannon cannon);
    double getDistanceToTarget(Cannon cannon);

    double maxBoreLength; // meters
    double maxBoreWidth; // meters
    double maxGunPowderMass; // Kg
    double maxAngle; // degrees
    double maxPlatformHeight; // meters
    double targetDistance; // meters

    int totalGenerations;
    int childrenPerGeneration;

    double gravity;
public:
    void simulate() override;
    CannonSimulation(int totalGenerations, int maxPopulation, int childrenPerGeneration, double targetDistance,
                         double maxBoreLength, double maxBoreWidth, double maxGunPowderMass, double maxAngle,
                         double maxPlatformHeight, double mutationChance, double gravity);
};