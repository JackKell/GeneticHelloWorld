#pragma once

#include "LivingString.h"
#include "Simulation.h"

class LivingStringSimulation : public Simulation<LivingString> {
protected:
    string targetDna;

    virtual LivingString createRandomIndividual() override;
    virtual LivingString breed(LivingString livingString1, LivingString livingString2) override;
    virtual void mutate(LivingString &livingString) override;
    virtual void fitnessTest(LivingString &livingString) override;
    virtual bool reachedGoal() override;
    virtual void printPopulation() override;

public:
    LivingStringSimulation(string targetDna, int maxPopulation, int childrenPerGeneration, double mutationChance,
                               int printEveryNthGeneration);
};
