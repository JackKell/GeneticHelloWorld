#ifndef GENETICHELLOWORLD_SIMULATION_H
#define GENETICHELLOWORLD_SIMULATION_H

#include "Animal.h"
#include <vector>
#include <c++/ctime>
#include <algorithm>

using std::vector;
using std::sort;

template <class T> class Simulation {
protected:
    vector<T> population;
    int generation;
    int maxPopulation;
    double mutationChance;

    double randomDouble(double maxValue, double minValue = 0) {
        double f = (double)rand() / RAND_MAX;
        return minValue + f * (maxValue - minValue);
    }

    virtual T createRandomIndividual() = 0;
    virtual T breed(T, T) = 0;
    virtual void mutate(T &animal) = 0;
    virtual void fitnessTest(T &animal) = 0;

    virtual bool reachedGoal() = 0;

    virtual void generateRandomPopulation() {
        for (int i = 0; i < maxPopulation; ++i) {
            T individual = createRandomIndividual();
            fitnessTest(individual);
            population.push_back(individual);
        }
    }

    virtual void testPopulation() = 0;

    T getRandomIndividual() {
        return population.at(rand() % population.size());
    }

    virtual void printPopulation() {
        for (T animal : population) {
            animal.toString();
        }
    }

    void trimPopulation() {
        sort(population.begin(), population.end());
        for (int i = 0; i < (maxPopulation - population.size()); i++) {
            population.pop_back();
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