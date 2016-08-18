#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#define _USE_MATH_DEFINES
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cfloat>
#include "CannonSimulation.h"

using std::isnan;
using std::rand;
using std::cout;
using std::endl;
using std::string;
using std::abs;

CannonSimulation::CannonSimulation(int totalGenerations, int maxPopulation, int childrenPerGeneration, double targetDistance,
                                   double maxBoreLength, double maxBoreWidth, double maxGunPowderMass, double maxAngle,
                                   double maxPlatformHeight, double mutationChance, double gravity, int printEveryNthGeneration)
        : Simulation(maxPopulation, childrenPerGeneration, mutationChance, printEveryNthGeneration) {
    this->maxBoreLength = maxBoreLength;
    this->maxBoreWidth = maxBoreWidth;
    this->maxGunPowderMass = maxGunPowderMass;
    this->maxAngle = maxAngle;
    this->maxPlatformHeight = maxPlatformHeight;
    this->targetDistance = targetDistance;
    this->totalGenerations = totalGenerations;
    this->gravity = gravity;
}

Cannon CannonSimulation::breed(Cannon cannon1, Cannon cannon2) {
    const double boreWidth = randomDouble(cannon1.boreWidth, cannon2.boreWidth);
    const double boreLength = randomDouble(cannon1.boreLength, cannon2.boreLength);
    const double angle = randomDouble(cannon1.launchAngle, cannon2.launchAngle);
    const double platformHeight = randomDouble(cannon1.platformHeight, cannon2.platformHeight);
    const double gunPowderMass = randomDouble(cannon1.gunPowderMass, cannon2.gunPowderMass);
    Cannon newCannon = Cannon(boreWidth, boreLength, gunPowderMass, angle, platformHeight);
    if ((rand() % 100) < mutationChance) {
        mutate(newCannon);
    }
    fitnessTest(newCannon);
    return newCannon;
}

void CannonSimulation::fitnessTest(Cannon &cannon) {
    const double distanceToTarget = getDistanceToTarget(cannon);
    const double flightTime = getFlightTime(cannon);
    if (flightTime != 0 && distanceToTarget != targetDistance) {
        cannon.fitnessValue = distanceToTarget + flightTime * 70;
    } else {
        cannon.fitnessValue = DBL_MAX;
    }
}

bool CannonSimulation::reachedGoal() {
    bool generationsCondition = totalGenerations <= currentGeneration;
    return generationsCondition;
}

void CannonSimulation::printPopulation() {
    cout << "Generation: " << currentGeneration << endl;
    const string titleSeparator = "  |  ";
    const string separator = " | ";
    cout << "R " << titleSeparator
         << "FV" << titleSeparator
         << "BL(m)" << titleSeparator
         << "BW(m)" << titleSeparator
         << "GPM(Kg)" << titleSeparator
         << "PH(m)" << titleSeparator
         << "A(d)" << titleSeparator
         << "CL(m)" << titleSeparator
         << "MV(m/s)" << titleSeparator
         << "D(m)" << titleSeparator
         << "T(s)"
         << endl;
    for (int i = 0; i < population.size(); i++) {
        Cannon cannon = population.at((unsigned long long int) i);
        cout << (i + 1) << " - "
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
        sortPopulation();
        if (currentGeneration % printEveryNthGeneration == 0) {
            printPopulation();
        }
        addChildrenToPopulation();
        trimPopulation();
        currentGeneration++;
    }
    printPopulation();
}

Cannon CannonSimulation::createRandomIndividual() {
    const double boreWidth = randomDouble(maxBoreWidth);
    const double boreLength = randomDouble(maxBoreLength);
    const double gunPowderMass = randomDouble(maxGunPowderMass);
    const double angle = randomDouble(maxAngle);
    const double platformHeight = randomDouble(maxPlatformHeight);
    return Cannon(boreWidth, boreLength, gunPowderMass, angle, platformHeight);
}

// super helpful for external balistic calculations
// https://en.wikipedia.org/wiki/Trajectory_of_a_projectile

double CannonSimulation::getMaximumHeight(Cannon cannon) {
    return 0;
}

double CannonSimulation::getFlightTime(Cannon cannon) {
    const double muzzleVelocity = cannon.getMuzzleVelocity();
    const double angleRadians = cannon.launchAngle * M_PI / 180;
    double flightTime = getDistanceShot(cannon) / (muzzleVelocity * cos(angleRadians));
    flightTime = isnan(flightTime) ? 0 : flightTime;
    return flightTime;
}

double CannonSimulation::getDistanceShot(Cannon cannon) {
    // TODO: add wind resistance to calculations
    const double muzzleVelocity = cannon.getMuzzleVelocity();
    const double angleRadians = cannon.launchAngle * M_PI / 180;
    const double startHeight = cannon.getStartHeight();
    const double distance = ((muzzleVelocity * cos(angleRadians)) / gravity) * (muzzleVelocity * sin(angleRadians) + sqrt((muzzleVelocity * sin(angleRadians)) + 2 * gravity * startHeight));
    return distance;
}

double CannonSimulation::getDistanceToTarget(Cannon cannon) {
    return abs(targetDistance - getDistanceShot(cannon));
}

void CannonSimulation::mutate(Cannon &cannon) {
    int randNum = rand() % 5;
    switch (randNum) {
        case 0:
            cannon.boreWidth = randomDouble(maxBoreWidth, 0);
            break;
        case 1:
            cannon.boreLength = randomDouble(maxBoreLength, 0);
            break;
        case 2:
            cannon.gunPowderMass = randomDouble(maxGunPowderMass, 0);
            break;
        case 3:
            cannon.launchAngle = randomDouble(maxBoreWidth, 0);
            break;
        case 4:
            cannon.platformHeight = randomDouble(maxPlatformHeight, 0);
            break;
        default:
            cout << "There is a big problem! :(" << endl;
    }
}

#pragma clang diagnostic pop
