#include <time.h>
#include "CannonSimulation.h"
#include "LivingStringSimulation.h"

void cannonTest() {
    // number of individuals in each generation
    const int maxPopulation = 100;
    // percentage chance that a child will be mutated between generations
    const double mutationChance = 6;
    // number of generations to run the simulation
    const int totalGenerations = 1;
    const int printEveryNthGeneration = 25;
    // number of children born every generation
    const int childrenPerGen = 12;

    const double targetDistance = 457.2; // meters

    const double maxBoreLength = 1.524; // meters
    const double maxBoreWidth = 0.3048; // meters
    const double maxGunPowderMass = 1.36078; // kilograms
    const double maxAngle = 90; // degrees
    const double maxPlatformHeight = 3.048; // meters

    CannonSimulation cannonSimulation = CannonSimulation(totalGenerations, maxPopulation, childrenPerGen,
                                                         targetDistance, maxBoreLength, maxBoreWidth, maxGunPowderMass,
                                                         maxAngle, maxPlatformHeight, mutationChance, Gravity::EARTH,
                                                         printEveryNthGeneration);
    // run the simulation
    cannonSimulation.simulate();
}

int main() {
    // sets the random seed
    srand((unsigned int) time(NULL));

    LivingStringSimulation livingStringSimulation = LivingStringSimulation("Hello World", 50, 20, 6, 100);

    livingStringSimulation.simulate();
}

