//
// Created by jackkell on 11/21/15.
//

#include <string.h>
#include <iostream>
#include "Animal.h"

Animal::Animal() {
    this->genes = "";
    this->fitnessScore = 0;
}

Animal::~Animal() { };

Animal::Animal(string genes) {
    this->genes = genes;
    this->fitnessScore = 0;
}

string Animal::GetGene() {
    return genes;
}


string Animal::ToString() {
    return GetGene();
}
