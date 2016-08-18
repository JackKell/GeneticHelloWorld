#pragma once

#include <string>
#include "Animal.h"

using std::string;

class LivingString : public Animal {
public:
    LivingString(string dna);
    string dna;
};
