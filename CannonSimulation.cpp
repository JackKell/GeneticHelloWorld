#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#define _USE_MATH_DEFINES
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "CannonSimulation.h"

using std::sort;
using std::isnan;
using std::rand;
using std::cout;
using std::endl;
using std::string;

CannonSimulation::CannonSimulation(int totalGenerations, int maxPopulation, int childrenPerGeneration, double targetDistance,
                                   double maxBoreLength, double maxBoreWidth, double maxGunPowderMass, double maxAngle,
                                   double maxPlatformHeight, double mutationChance, double gravity)
        : Simulation(maxPopulation, mutationChance) {
    this->maxBoreLength = maxBoreLength;
    this->maxBoreWidth = maxBoreWidth;
    this->maxGunPowderMass = maxGunPowderMass;
    this->maxAngle = maxAngle;
    this->maxPlatformHeight = maxPlatformHeight;
    this->targetDistance = targetDistance;
    this->totalGenerations = totalGenerations;
    this->childrenPerGeneration = childrenPerGeneration;
    this->gravity = gravity;
}

double CannonSimulation::randomDoubleBetweenDataMembers(double value1, double value2) {
    double newValue = 0;
    if (value1 > value2) {
        newValue = randomDouble(value1, value2);
    } else {
        newValue = randomDouble(value2, value1);
    }
    return newValue;
}

Cannon CannonSimulation::breed(Cannon cannon1, Cannon cannon2) {
    double boreWidth = randomDoubleBetweenDataMembers(cannon1.boreWidth, cannon2.boreWidth);
    double boreLength = randomDoubleBetweenDataMembers(cannon1.boreLength, cannon2.boreLength);
    double angle = randomDoubleBetweenDataMembers(cannon1.launchAngle, cannon2.launchAngle);
    double platformHeight = randomDoubleBetweenDataMembers(cannon1.platformHeight, cannon2.platformHeight);
    double gunPowderMass = randomDoubleBetweenDataMembers(cannon1.gunPowderMass, cannon2.gunPowderMass);
    Cannon newCannon = Cannon(boreWidth, boreLength, gunPowderMass, angle, platformHeight);
    if ((rand() % 100) < mutationChance) {
        mutate(newCannon);
    }
    return newCannon;
}

void CannonSimulation::fitnessTest(Cannon &cannon) {
    double fitnessValue = 0;
    double distanceToTarget = getDistanceToTarget(cannon);
    double flightTime = getFlightTime(cannon);
    if (flightTime != 0 && distanceToTarget != targetDistance) {
        fitnessValue = distanceToTarget + flightTime * 70;
    } else {
        fitnessValue = 10000;
    }
    cannon.fitnessValue = fitnessValue;
}

bool CannonSimulation::reachedGoal() {
    bool generationsCondition = currentGeneration > totalGenerations;
    return generationsCondition;
}

void CannonSimulation::testPopulation() {
    for (Cannon &cannon : population) {
        fitnessTest(cannon);
    }
}

void CannonSimulation::printPopulation() {
    cout << "Generation: " << currentGeneration << endl;
    string separator = " | ";
    cout << " FV" << separator
         << "BL(m)" << separator
         << "BW(m)" << separator
         << "GPM(Kg)" << separator
         << "PH(m)" << separator
         << "A(d)" << separator
         << "CL(m)" << separator
         << "MV(m/s)" << separator
         << "D(m)" << separator
         << "T(s)"
         << endl;
    for (Cannon &cannon : population) {
        cout << "- "
             << cannon.fitnessValue << separator
             << cannon.boreLength << separator
             << cannon.boreWidth << separator
             << cannon.gunPowderMass << separator
             << cannon.platformHeight << separator
             << cannon.launchAngle << separator
             << cannon.getChargeLength() << separator
             << cannon.getMuzzleVelocity() << separator
             << getDistanceShot(cannon) << separator
             << getFlightTime(cannon)
             << endl;
    }
}

void CannonSimulation::simulate() {
    generateRandomPopulation();
    while (!reachedGoal()) {
        sort(population.begin(), population.end());
        if (currentGeneration % 10 == 0) {
            printPopulation();
        }

        haveChildren();
        trimPopulation();
        currentGeneration++;
    }
}

Cannon CannonSimulation::createRandomIndividual() {
    double boreWidth = randomDouble(maxBoreWidth);
    double boreLength = randomDouble(maxBoreLength);
    double gunPowderMass = randomDouble(maxGunPowderMass);
    double angle = randomDouble(maxAngle);
    double platformHeight = randomDouble(maxPlatformHeight);
    return Cannon(boreWidth, boreLength, gunPowderMass, angle, platformHeight);
}

// super helpful
// https://en.wikipedia.org/wiki/Trajectory_of_a_projectile

double CannonSimulation::getMaximumHeight(Cannon cannon) {
    return 0;
}

double CannonSimulation::getFlightTime(Cannon cannon) {
    double muzzleVelocity = cannon.getMuzzleVelocity();
    double angleRadians = cannon.launchAngle * M_PI / 180;
    double flightTime = getDistanceShot(cannon) / (muzzleVelocity * cos(angleRadians));
    flightTime = isnan(flightTime) ? 0 : flightTime;
    return flightTime;
}

double CannonSimulation::getDistanceShot(Cannon cannon) {
    // TODO: add wind resistance to calculations
    double muzzleVelocity = cannon.getMuzzleVelocity();
    double angleRadians = cannon.launchAngle * M_PI / 180;
    double startHeight = cannon.getStartHeight();
    double distance = ((muzzleVelocity * cos(angleRadians)) / gravity) * (muzzleVelocity * sin(angleRadians) + sqrt((muzzleVelocity * sin(angleRadians)) + 2 * gravity * startHeight));
    return distance;
}

double CannonSimulation::getDistanceToTarget(Cannon cannon) {
    double distanceToTarget = targetDistance - getDistanceShot(cannon);
    distanceToTarget = distanceToTarget < 0 ? distanceToTarget * -1 : distanceToTarget;
    return distanceToTarget;
}

double CannonSimulation::mutateDouble(double value, double percentageChance, double maxValue) {
    double newValue = 0;
    newValue = randomDouble((1 + percentageChance) * value, (1 - percentageChance) * value);
    if (newValue > maxValue) {
        newValue = maxValue;
    }
    return newValue;
}

void CannonSimulation::mutate(Cannon &cannon) {
    int randNum = rand() % 5;
    switch (randNum) {
        case 0:
            cannon.boreWidth = mutateDouble(cannon.boreWidth, 0.2, maxBoreWidth);
            break;
        case 1:
            cannon.boreLength = mutateDouble(cannon.boreLength, 0.2, maxBoreLength);
            break;
        case 2:
            cannon.gunPowderMass = mutateDouble(cannon.gunPowderMass, 0.2, maxGunPowderMass);
            break;
        case 3:
            cannon.launchAngle = mutateDouble(cannon.launchAngle, 0.2, maxAngle);
            break;
        case 4:
            cannon.platformHeight = mutateDouble(cannon.platformHeight, 0.2, maxPlatformHeight);
            break;
        default:
            cout << "There is a big problem! :(" << endl;
    }
}

void CannonSimulation::haveChildren() {
    for (int i = 0; i < childrenPerGeneration; i++) {
        int index1 = rand() % maxPopulation;
        int index2 = rand() % maxPopulation;
        while (index1 == index2) {
            index2 = rand() % maxPopulation;
        }
        Cannon cannon1 = population.at((unsigned long long int) index1);
        Cannon cannon2 = population.at((unsigned long long int) index2);
        Cannon newCannon = breed(cannon1, cannon2);
        fitnessTest(newCannon);
        population.push_back(newCannon);
    }
}

#pragma clang diagnostic pop
