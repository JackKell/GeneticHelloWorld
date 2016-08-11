#include "Cannon.h"

#define _USE_MATH_DEFINES
#include <math.h>

const double Cannon::GUN_POWDER_DENSITY_I = 55.0; // lb / ft^3
const double Cannon::GAS_PRESSURE_RATIO_TO_ATM_I = 1600.0; // imperial ratio
const double Cannon::ATM_I = 14.7*32.2*144; // 68160.96 lbw / ft^2

const double Cannon::GUN_POWDER_DENSITY =  881.071383; // kg / m^3
const double Cannon::GAS_PRESSURE_RATIO_TO_ATM = 56515.7; // metric ratio
const double Cannon::ATM = 2872.310354; // kg / m^2



double Cannon::getChargeLength_I() {
    return gunPowderMass * 4 / (M_PI * boreWidth * boreWidth * GUN_POWDER_DENSITY_I);
}

double Cannon::getChargeLength() {
    return gunPowderMass * 4 / (M_PI * boreWidth * boreWidth * GUN_POWDER_DENSITY);
}


double Cannon::getMuzzleVelocity() {
    double muzzleVelocity = sqrt(2 * GAS_PRESSURE_RATIO_TO_ATM_I * ATM_I / GUN_POWDER_DENSITY_I) * sqrt(gunPowderMass / (ballMass + gunPowderMass / 3) * log(boreLength /
                                                                                                                                                                     getChargeLength_I()));
    return muzzleVelocity;
}

double Cannon::getMuzzleVelocity_M() {
    double muzzleVelocity = sqrt(2 * GAS_PRESSURE_RATIO_TO_ATM * ATM / GUN_POWDER_DENSITY) * sqrt(gunPowderMass / (ballMass + gunPowderMass / 3) * log(boreLength /
                                                                                                                                                               getChargeLength_I()));
    return muzzleVelocity;
}

Cannon::Cannon(double boreWidth, double boreLength, double gunPowderMass, double ballMass) {
    this->boreWidth = boreWidth;
    this->boreLength = boreLength;
    this->gunPowderMass = gunPowderMass;
    this->ballMass = ballMass;
}

Cannon::~Cannon() {}




