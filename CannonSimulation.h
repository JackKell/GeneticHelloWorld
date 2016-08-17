#pragma once

#include "Simulation.h"
#include "Cannon.h"

namespace Gravity {
    const double SUN = 274; // m / s^2
    const double JUPITER = 24.92;
    const double NEPTUNE = 11.15;
    const double SATURN = 10.44;
    const double URANUS = 8.87;
    const double VENUS = 8.87;
    const double MARS = 3.71;
    const double MERCURY = 3.7;
    const double PLUTO = 0.58;
    const double EARTH = 9.807;
    const double MOON = 1.625;
}

class CannonSimulation : public Simulation<Cannon> {
private:
    Cannon createRandomIndividual() override;
    Cannon breed(Cannon cannon1, Cannon cannon2) override;

    void fitnessTest(Cannon &cannon) override;
    bool reachedGoal() override;

    void testPopulation() override;
    void printPopulation() override;

    void mutate(Cannon &cannon) override;
    double mutateDouble(double value, double precentChange, double maxValue);
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
public:
    static const double EARTH_G;

    void simulate() override;
    CannonSimulation(int totalGenerations, int maxPopulation, int childrenPerGeneration, double targetDistance,
                         double maxBoreLength, double maxBoreWidth, double maxGunPowderMass, double maxAngle,
                         double maxPlatformHeight, double mutationChance, double gravity);
};