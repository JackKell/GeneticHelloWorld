class Cannon {
private:
    // meters
    double boreWidth;
    // meters
    double boreLength;
    // degrees
    double angle;
    // meters
    double height;
    // Kg
    double gunPowderMass;
    // Kg
    double ballMass;


public:
    static const double GUN_POWDER_DENSITY_I;
    static const double GAS_PRESSURE_RATIO_TO_ATM_I;
    static const double ATM_I;

    static const double GUN_POWDER_DENSITY;
    static const double GAS_PRESSURE_RATIO_TO_ATM;
    static const double ATM;

    Cannon(double boreWidth, double boreLength, double gunPowderMass, double ballMass);
    ~Cannon();

    double getChargeLength_I();
    double getChargeLength();
    double getMuzzleVelocity();
    double getMuzzleVelocity_M();
};
