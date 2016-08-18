#pragma once

#include <vector>
#include <algorithm>

using std::vector;
using std::sort;

template <class T> class Simulation {
protected:
    vector<T> population;
    int currentGeneration;
    int maxPopulation;
    double mutationChance;
    int printEveryNthGeneration;

    virtual T createRandomIndividual() = 0;
    virtual void addChildrenToPopulation() = 0;
    virtual T breed(T, T) = 0;
    virtual void mutate(T &) = 0;
    virtual void fitnessTest(T &) = 0;
    virtual bool reachedGoal() = 0;
    virtual void testPopulation() = 0;

    virtual void generateRandomPopulation() {
        for (int i = 0; i < maxPopulation; ++i) {
            T individual = createRandomIndividual();
            fitnessTest(individual);
            population.push_back(individual);
        }
    }

    T getRandomIndividual() {
        return population.at(rand() % population.size());
    }

    virtual void printPopulation() {
        for (T animal : population) {
            animal.toString();
        }
    }

    virtual void trimPopulation() {
        sort(population.begin(), population.end());
        for (int i = 0; i < (maxPopulation - population.size()); i++) {
            population.pop_back();
        }
    }

    double randomDouble(double maxValue, double minValue = 0) {
        double f = (double)rand() / RAND_MAX;
        return minValue + f * (maxValue - minValue);
    }

public:
    virtual void simulate() = 0;

    int getCurrentGeneration() {
        return currentGeneration;
    }

    int getMaxPopulation() {
        return maxPopulation;
    }

    double getMutationChance(){
        return mutationChance;
    }

    Simulation(int maxPopulation, double mutationChance, int printEveryNthGeneration) {
        this->currentGeneration = 0;
        this->maxPopulation = maxPopulation;
        this->mutationChance = mutationChance;
        this->printEveryNthGeneration = printEveryNthGeneration;
    }
};