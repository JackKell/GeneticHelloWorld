#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#include "Cannon.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <c++/cmath>

using std::isnan;

const double Cannon::GUN_POWDER_DENSITY =  881.071383;
const double Cannon::CAST_IRON_DENSITY = 6800;
const double Cannon::R = 56496.1;
const double Cannon::ATM = 2872.310354;

double Cannon::getChargeLength() {
    return gunPowderMass * 4 / (M_PI * boreWidth * boreWidth * GUN_POWDER_DENSITY);
}

double Cannon::getBallMass() {
    return (4/3) * M_PI * CAST_IRON_DENSITY * pow((boreWidth / 2), 3);
}

double Cannon::getMuzzleVelocity() {
    double muzzleVelocity = (
            sqrt(2 * R * ATM / GUN_POWDER_DENSITY) *
            sqrt(gunPowderMass / (getBallMass() + gunPowderMass / 3) *
                 log(boreLength / getChargeLength())
            )
    );
    muzzleVelocity = isnan(muzzleVelocity) ? 0 : muzzleVelocity;
    return muzzleVelocity;
}

Cannon::Cannon(double boreWidth, double boreLength, double gunPowderMass, double angle, double height) {
    this->boreWidth = boreWidth;
    this->boreLength = boreLength;
    this->gunPowderMass = gunPowderMass;
    this->angle = angle;
    this->platformHeight = height;
}

double Cannon::getStartHeight() {
    double angleRadians = angle * M_PI / 180;
    double cannonToPlatformHeight = sin(angleRadians) * boreLength;
    return cannonToPlatformHeight + platformHeight;
}

#pragma clang diagnostic pop