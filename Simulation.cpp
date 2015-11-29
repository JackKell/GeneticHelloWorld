//
// Created by jackkell on 11/28/15.
//

#include "Simulation.h"
#include <cmath>
#include <iostream>

using std::cout;
using std::to_string;

Simulation::Simulation() {
    this->generation = 0;
}

Simulation::Simulation(string answerGene, uint startingPopulationSize, uint mutationChance) {
    this->answerGene = answerGene;
    this->startingPopulationSize = startingPopulationSize;
    this-> mutationChance = mutationChance;
    this->generation = 0;
    GenerateRandomPopulation();
}

Simulation::~Simulation() {}

void Simulation::GenerateRandomPopulation() {
    for (int i = 0; i < startingPopulationSize; i++) {
        string newRandomGene = "";
        for (int j = 0; j < answerGene.size(); j++) {
            newRandomGene += (char)(rand() % 256);
        }
        population.push_back(Animal(newRandomGene));
    }
}

Animal Simulation::GetMostFitAnimal() {
    return Animal();
}

void Simulation::TestPopulation() {
    for (Animal currentAnimal : this->population) {
        int fitnessScore = 0;
        for (int i = 0; i < answerGene.size(); i++) {
            fitnessScore += 100 - abs(((int)currentAnimal.GetGene()[i] - (int)answerGene[i]));
        }
        currentAnimal.fitnessScore = fitnessScore;
    }
}


void Simulation::DisplayPopultation() {
    cout << "Generation " + to_string(this->generation);
    for (int i = 0; i < this->population.size(); i++) {
        cout << to_string(i) + " " + this->population[i].ToString();
    }
}
