#pragma once


#include "TurtleBot.h"
#include "Simulation.h"
#include "TurtleBotMap.h"

class TurtleBotSimulation : public Simulation<TurtleBot>{
private:
    int brainSize;
    Direction startDirection;
    TurtleBotMap turtleBotMap = TurtleBotMap();
    float outOfBoundsPenalty;
    float goalReward;
    int totalGenerations;
    float actionCost;
    float finishOnEndReward;
    float finishOffEndPenalty;
    float outOfActionsPenalty;

    bool isOutOfBounds(TurtleBot turtleBot);
protected:
    virtual TurtleBot createRandomIndividual() override;

    virtual TurtleBot breed(TurtleBot turtleBot1, TurtleBot turtleBot2) override;

    virtual float testSimilarity(TurtleBot turtleBot1, TurtleBot turtleBot2) override;

    virtual void mutate(TurtleBot &turtleBot) override;

    virtual void fitnessTest(TurtleBot &turtleBot) override;

    virtual bool reachedGoal() override;

    virtual void printPopulation() override;

    virtual void sortPopulation() override;

    virtual void addChildrenToPopulation() override;

public:
    TurtleBotSimulation(int totalGenerations, int childrenPerGeneration, double mutationChance,
                            int printEveryNthGeneration, int maxPopulation, int brainSize, Direction startDirection,
                            TurtleBotMap turtleBotMap, float outOfBoundsPenalty, float goalReward, float actionCost,
                            float finishOnEndReward, float finishOffEndReward, float outOfActionsPenalty);

};
