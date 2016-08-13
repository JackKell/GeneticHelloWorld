#ifndef GENETICHELLOWORLD_SIMULATION_H
#define GENETICHELLOWORLD_SIMULATION_H

#include "Animal.h"
#include <vector>
#include <c++/ctime>

using std::vector;

template <class T> class Simulation {
protected:
    vector<T> population;
    int generation;
    int maxPopulation;
    double mutationChance;

    double randomDouble(double maxValue) {

        return ((((double)rand()*(maxValue) / RAND_MAX) - maxValue) *(-1));
    }

    virtual T createRandomIndividual() = 0;
    virtual T breed(T, T) = 0;

    virtual void fitnessTest(T &animal) = 0;
    virtual bool reachedGoal() = 0;

    virtual void generateRandomPopulation() {
        for (int i = 0; i < maxPopulation; ++i) {
            population.push_back(createRandomIndividual());
        }
    }

    virtual void testPopulation() = 0;

    virtual void printPopulation() {
        for (T animal : population) {
            animal.toString();
        }
    }

public:
    virtual void simulate() = 0;

    int getGeneration() {
        return generation;
    }

    int getMaxPopulation() {
        return maxPopulation;
    }

    double getMutationChance(){
        return mutationChance;
    }

    Simulation(int maxPopulation, double mutationChance) {
        this->generation = 0;
        this->maxPopulation = maxPopulation;
        this->mutationChance = mutationChance;
    }
};

#endif