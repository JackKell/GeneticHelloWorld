#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#define _USE_MATH_DEFINES
#include <c++/cstdlib>
#include "CannonSimulation.h"
#include <math.h>
#include <c++/iostream>
#include <c++/iomanip>
#include <string>
#include <c++/cmath>
#include <algorithm>

using std::sort;
using std::isnan;
using std::rand;
using std::cout;
using std::endl;
using std::setw;
using std::string;

const double CannonSimulation::EARTH_G = 9.807; // m / s^2

Cannon CannonSimulation::breed(Cannon cannon1, Cannon cannon2) {
    double averageBoreWidth = (cannon1.boreWidth + cannon2.boreWidth) / 2;
    double averageBoreLength = (cannon1.boreLength + cannon2.boreLength) / 2;
    double averageAngle = (cannon1.angle + cannon2.angle) / 2;
    double averagePlatformHeight = (cannon1.platformHeight + cannon2.platformHeight) / 2;
    double averageGunPowderMass = (cannon1.gunPowderMass + cannon2.gunPowderMass) / 2;
    Cannon newCannon = Cannon(averageBoreWidth, averageBoreLength, averageGunPowderMass, averageAngle, averagePlatformHeight);
    if ((rand() % 100) < mutationChance) {
        mutate(newCannon);
    }
}

void CannonSimulation::fitnessTest(Cannon &cannon) {
    double fitnessValue = 0;
    double distanceToTarget = getDistanceToTarget(cannon);
    double flightTime = getFlightTime(cannon);
    if (flightTime != 0 && distanceToTarget != targetDistance) {
        fitnessValue = distanceToTarget + flightTime * 10;
    } else {
        fitnessValue = 5000;
    }
    cannon.fitnessValue = fitnessValue;
}

bool CannonSimulation::reachedGoal() {
    return false;
}

void CannonSimulation::testPopulation() {
    for (Cannon &cannon : population) {
        fitnessTest(cannon);
    }
}

void CannonSimulation::printPopulation() {
    cout << "Generation: " << generation << endl;
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
             << cannon.angle << separator
             << cannon.getChargeLength() << separator
             << cannon.getMuzzleVelocity() << separator
             << getDistanceShot(cannon) << separator
             << getFlightTime(cannon)
             << endl;
    }
}

void CannonSimulation::simulate() {
    generateRandomPopulation();
    sort(population.begin(), population.end());
    printPopulation();
    generation++;

}

CannonSimulation::CannonSimulation(int maxPopulation, double mutationChance, double targetDistance,
                                   double maxBoreLength, double maxBoreWidth, double maxGunPowderMass,
                                   double maxAngle, double maxPlatformHeight)
        : Simulation(maxPopulation, mutationChance) {
    this->maxBoreLength = maxBoreLength;
    this->maxBoreWidth = maxBoreWidth;
    this->maxGunPowderMass = maxGunPowderMass;
    this->maxAngle = maxAngle;
    this->maxPlatformHeight = maxPlatformHeight;
    this->targetDistance = targetDistance;
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
    double angleRadians = cannon.angle * M_PI / 180;
    double flightTime = getDistanceShot(cannon) / (muzzleVelocity * cos(angleRadians));
    flightTime = isnan(flightTime) ? 0 : flightTime;
    return flightTime;
}

double CannonSimulation::getDistanceShot(Cannon cannon) {
    // TODO: add wind resistance to calculations
    double muzzleVelocity = cannon.getMuzzleVelocity();
    double angleRadians = cannon.angle * M_PI / 180;
    double startHeight = cannon.getStartHeight();
    double distance = ((muzzleVelocity * cos(angleRadians)) / EARTH_G) * (muzzleVelocity * sin(angleRadians) + sqrt((muzzleVelocity * sin(angleRadians)) + 2 * EARTH_G * startHeight));
    return distance;
}

double CannonSimulation::getDistanceToTarget(Cannon cannon) {
    double distanceToTarget = targetDistance - getDistanceShot(cannon);
    distanceToTarget = distanceToTarget < 0 ? distanceToTarget * -1 : distanceToTarget;
    return distanceToTarget;
}

void CannonSimulation::mutate(Cannon &cannon) {

}

#pragma clang diagnostic pop
