#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#include "Cannon.h"

#define _USE_MATH_DEFINES
#include <cmath>

using std::isnan;

const double Cannon::GUN_POWDER_DENSITY = 881.071383;
const double Cannon::CAST_IRON_DENSITY = 6800;
const double Cannon::R = 56496.1;
const double Cannon::ATM = 2872.310354;

inline double Cannon::getChargeLength() {
    return gunPowderMass * 4 / (M_PI * boreWidth * boreWidth * GUN_POWDER_DENSITY);
}

inline double Cannon::getBallMass() {
    return (4/3) * M_PI * CAST_IRON_DENSITY * pow((boreWidth / 2), 3);
}

double Cannon::getMuzzleVelocity() {
    double muzzleVelocity = 0;
    const double chargeLength = getChargeLength();

    if (chargeLength + boreWidth > boreLength) {
        muzzleVelocity = 0;
    } else {
        muzzleVelocity = (
                sqrt(2 * R * ATM / GUN_POWDER_DENSITY) *
                sqrt(gunPowderMass / (getBallMass() + gunPowderMass / 3) *
                     log(boreLength / getChargeLength())
                )
        );
        muzzleVelocity = isnan(muzzleVelocity) ? 0 : muzzleVelocity;
    }

    return muzzleVelocity;
}

Cannon::Cannon(double boreWidth, double boreLength, double gunPowderMass, double launchAngle, double platformHeight) {
    this->boreWidth = boreWidth;
    this->boreLength = boreLength;
    this->gunPowderMass = gunPowderMass;
    this->launchAngle = launchAngle;
    this->platformHeight = platformHeight;
}

double Cannon::getStartHeight() {
    const double angleRadians = launchAngle * M_PI / 180;
    const double cannonToPlatformHeight = sin(angleRadians) * boreLength;
    return cannonToPlatformHeight + platformHeight;
}

/*
     * The below values should be used to check if the cannons are working properly
     * under normal earth gravity at sea level air pressure
     *
     * These are the source values
     * d = 0.3041 feet
     * L = 4.8666 feet
     * powderWeight = 1.25 lbs
     * ballWeight = 6 lbs
     * velocity = 1456.15 ft / sec
     *
     * These are the values converted to metric
     * d = 0.09271 meters
     * L = 1.48336 meters
     * powderWeight = 0.5669905 kgs
     * ballWeight = 2.72155 kgs
     * velocity = 443.83452 meters / sec
     */

#pragma clang diagnostic pop