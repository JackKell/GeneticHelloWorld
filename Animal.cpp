#include <iostream>
#include "Animal.h"

using std::cout;
using std::endl;

Animal::Animal() {
    this->fitnessValue = 0;
}

void Animal::toString() {
    cout << fitnessValue << endl;
}




