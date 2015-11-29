//
// Created by jackkell on 11/21/15.
//

#pragma once

#include <string>

using std::string;

class Animal {
private:
    string genes;

public:
    int fitnessScore;
    Animal();
    Animal(string genes);
    ~Animal();
    string GetGene();
    string ToString();
};
