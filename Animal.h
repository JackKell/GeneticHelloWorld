//
// Created by jackkell on 11/21/15.
//

#ifndef TESTPROJECT_ANIMAL_H
#define TESTPROJECT_ANIMAL_H

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
};


#endif //TESTPROJECT_ANIMAL_H
