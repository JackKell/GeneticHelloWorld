#ifndef GENETICHELLOWORLD_CANNONSIMULATION_H
#define GENETICHELLOWORLD_CANNONSIMULATION_H

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

public:
    static const double EARTH_G; // m / s^2

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


    void simulate() override;
    CannonSimulation(int maxPopulation, double mutationChance, double targetDistance,
                     double maxBoreLength, double maxBoreWidth, double maxGunPowderMass,
                     double maxAngle, double maxPlatformHeight);
};

#endif
