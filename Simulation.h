#pragma once

#include <vector>
#include <algorithm>
#include <string>

using std::vector;
using std::sort;
using std::string;

template <class T> class Simulation {
protected:
    vector<T> population;
    int currentGeneration;
    int maxPopulation;
    double mutationChance;
    int printEveryNthGeneration;
    int childrenPerGeneration;

    virtual T createRandomIndividual() = 0;
    virtual void addChildrenToPopulation() {
        for (int i = 0; i < childrenPerGeneration; i++) {
            const T individual1 = getRandomIndividual();
            const T individual2 = getRandomIndividual();
            T newIndividual = breed(individual1, individual2);
            population.push_back(newIndividual);
        }
    }
    virtual T breed(T, T) = 0;
    virtual void mutate(T &) = 0;
    virtual void fitnessTest(T &) = 0;
    virtual bool reachedGoal() = 0;
    virtual void printPopulation() = 0;

    virtual void sortPopulation() {
        sort(population.begin(), population.end());
    }

    virtual void generateRandomPopulation() {
        for (int i = 0; i < maxPopulation; ++i) {
            T individual = createRandomIndividual();
            fitnessTest(individual);
            population.push_back(individual);
        }
    }

    inline T getRandomIndividual() {
        return population.at(rand() % population.size());
    }

    virtual void trimPopulation() {
        sortPopulation();
        for (int i = 0; i < (maxPopulation - population.size()); i++) {
            population.pop_back();
        }
    }

    inline double randomDouble(double maxValue, double minValue = 0) {
        return minValue + ((double)rand() / RAND_MAX) * (maxValue - minValue);
    }

    string randomString(int length) {
        string randomString = "";
        for (int i = 0; i < length; i++) {
            int randomNum = (rand() % (127 - 32)) + 32;
            char randomChar = (char) randomNum;
            randomString += randomChar;
        }
        return randomString;
    }

public:
    virtual void simulate() {
        generateRandomPopulation();
        while (!reachedGoal()) {
            sortPopulation();
            if (currentGeneration % printEveryNthGeneration == 0) {
                printPopulation();
            }
            addChildrenToPopulation();
            trimPopulation();
            currentGeneration++;
        }
        printPopulation();
    };

    int getCurrentGeneration() {
        return currentGeneration;
    }

    int getMaxPopulation() {
        return maxPopulation;
    }

    double getMutationChance(){
        return mutationChance;
    }

    Simulation(int maxPopulation, int childrenPerGeneration, double mutationChance, int printEveryNthGeneration) {
        this->currentGeneration = 0;
        this->maxPopulation = maxPopulation;
        this->childrenPerGeneration = childrenPerGeneration;
        this->mutationChance = mutationChance;
        this->printEveryNthGeneration = printEveryNthGeneration;
    }
};