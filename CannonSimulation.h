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

public:
    static const double EARTH_G; // m / s^2

    double getMaximumHeight(Cannon cannon);
    double getFlightTime(Cannon cannon);
    double getRange(Cannon cannon);

    double maxBoreLength;
    double maxBoreWidth;
    double maxGunPowderMass;
    double maxAngle;
    double maxPlatformHeight;


    void simulate() override;
    CannonSimulation(int maxPopulation, double mutationChance, double maxBoreLength, double maxBoreWidth, double maxGunPowderMass, double maxAngle, double maxPlatformHeight);
};

#endif
