//
// Created by jackkell on 11/28/15.
//

#pragma once
#include <vector>
#include "Animal.h"

using std::string;
using std::vector;

class Simulation {
private:
    vector<Animal> population;
    uint generation;

public:
    string answerGene;
    uint startingPopulationSize;
    int mutationChance;

    Simulation();
    Simulation(string answerGene, uint startingPopulationSize, uint mutationChance = 0);
    ~Simulation();
    void GenerateRandomPopulation();
    void TestPopulation();
    Animal GetMostFitAnimal();
    void DisplayPopultation();
};