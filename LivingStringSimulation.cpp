#include "LivingStringSimulation.h"
#include <iostream>

using std::cout;
using std::endl;

LivingStringSimulation::LivingStringSimulation(string targetDna, int maxPopulation, int childrenPerGeneration, double mutationChance,
                                               int printEveryNthGeneration)
        : Simulation(maxPopulation, childrenPerGeneration, mutationChance, printEveryNthGeneration) {
    this->targetDna = targetDna;
}

LivingString LivingStringSimulation::createRandomIndividual() {
    string dna = randomString((int) targetDna.length());
    LivingString randomLivingString = LivingString(dna);
    fitnessTest(randomLivingString);
    return LivingString(dna);
}

LivingString LivingStringSimulation::breed(LivingString livingString1, LivingString livingString2) {
    const unsigned long long int dnaLength = livingString1.dna.length();
    const unsigned long long int randomIndex = rand() % dnaLength;
    string childDna = livingString1.dna.substr(0, randomIndex) + livingString2.dna.substr(randomIndex, dnaLength);
    LivingString child = LivingString(childDna);
    if (rand() % 100 <= mutationChance) {
        mutate(child);
    }
    fitnessTest(child);
    return child;
}

void LivingStringSimulation::mutate(LivingString &livingString) {
    string dna = livingString.dna;
    int randomIndex = (int) (rand() % (dna.length()));
    dna[randomIndex] = (char) (dna[randomIndex] + ((rand() % 51) - 25));
    livingString.dna = dna;
}

void LivingStringSimulation::fitnessTest(LivingString &livingString) {
    int fitnessValue = 0;
    const string dna = livingString.dna;
    for(int i = 0; i < targetDna.length(); i++) {
        char sourceChar = dna[i];
        char targetChar = targetDna[i];
        int delta = abs(sourceChar - targetChar);
        fitnessValue += delta;
    }
    livingString.fitnessValue = fitnessValue;
}

bool LivingStringSimulation::reachedGoal() {
    return (population.at(0)).dna == targetDna;
}

void LivingStringSimulation::printPopulation() {
    cout << "Generation: " << currentGeneration << endl;
    cout << "Rank | Fitness Value | DNA" << endl;
    for (int i = 0; i < population.size(); i++) {
        LivingString currentAnimal = population.at((unsigned long long int) i);
        cout << (i + 1) << " | "
             << currentAnimal.fitnessValue << " | "
             << currentAnimal.dna << endl;
    }
}
