#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#define _USE_MATH_DEFINES
#include <c++/cstdlib>
#include "CannonSimulation.h"
#include <math.h>
#include <c++/iostream>
#include <c++/iomanip>
#include <string>

using std::rand;
using std::cout;
using std::endl;
using std::setw;
using std::string;

const double CannonSimulation::EARTH_G = 9.807; // m / s^2

Cannon CannonSimulation::breed(Cannon cannon1, Cannon cannon2) {
    return Cannon(0, 0, 0, 0, 0);
}

void CannonSimulation::fitnessTest(Cannon &cannon) {

}

bool CannonSimulation::reachedGoal() {
    return false;
}

void CannonSimulation::testPopulation() {

}

void CannonSimulation::printPopulation() {
    string separator = " | ";
    cout << " FV" << separator
         << "BL(m)" << separator
         << "BW(m)" << separator
         << "GPM(Kg)" << separator
         << "PH(m)" << separator
         << "A(d)" << separator
         << "CL(m)" << separator
         << "MV(m/s)" << separator
         << "D(m)"
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
             << getRange(cannon)
             << endl;
    }
}

void CannonSimulation::simulate() {
    generateRandomPopulation();
    printPopulation();
}

CannonSimulation::CannonSimulation(int maxPopulation, double mutationChance, double maxBoreLength, double maxBoreWidth, double maxGunPowderMass, double maxAngle, double maxPlatformHeight)
        : Simulation(maxPopulation, mutationChance) {
    this->maxBoreLength = maxBoreLength;
    this->maxBoreWidth = maxBoreWidth;
    this->maxGunPowderMass = maxGunPowderMass;
    this->maxAngle = maxAngle;
    this->maxPlatformHeight = maxPlatformHeight;
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
    return getRange(cannon) / (muzzleVelocity * cos(angleRadians));
}

double CannonSimulation::getRange(Cannon cannon) {
    // TODO: add wind resistance to calculations
    double muzzleVelocity = cannon.getMuzzleVelocity();
    double angleRadians = cannon.angle * M_PI / 180;
    double startHeight = cannon.getStartHeight();
    double distance = ((muzzleVelocity * cos(angleRadians)) / EARTH_G) * (muzzleVelocity * sin(angleRadians) + sqrt((muzzleVelocity * sin(angleRadians)) + 2 * EARTH_G * startHeight));
    return distance;
}

#pragma clang diagnostic pop
