#ifndef GENETICHELLOWORLD_CANNON_H
#define GENETICHELLOWORLD_CANNON_H

#include "Animal.h"

class Cannon : public Animal{
public:
    double boreWidth; // meters
    double boreLength; // meters
    double launchAngle; // degrees
    double platformHeight; // meters
    double gunPowderMass; // kg

    static const double GUN_POWDER_DENSITY; // kg / m^3
    static const double CAST_IRON_DENSITY; // kg / m^3
    static const double R; // metric ratio
    static const double ATM; // kg / m^2

    Cannon(double boreWidth, double boreLength, double gunPowderMass, double launchAngle, double platformHeight);

    double getChargeLength(); // meters
    double getMuzzleVelocity(); // m/s
    double getBallMass(); // kg
    double getStartHeight(); // meters
};

#endif
