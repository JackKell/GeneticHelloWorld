#include <time.h>
#include "CannonSimulation.h"
#include "LivingStringSimulation.h"
#include "TurtleBot.h"
#include "TurtleBotSimulation.h"

void cannonTest() {
    // number of individuals in each generation
    const int maxPopulation = 100;
    // percentage chance that a child will be mutated between generations
    const double mutationChance = 50;
    // number of generations to run the simulation
    const int totalGenerations = 1000;
    const int printEveryNthGeneration = 25;
    // number of children born every generation
    const int childrenPerGen = 500;

    const double targetDistance = 25; // meters

    const double maxBoreLength = 1.524; // meters
    const double maxBoreWidth = 0.3048; // meters
    const double maxGunPowderMass = 1.36078; // kilograms
    const double maxAngle = 90; // degrees
    const double maxPlatformHeight = 3.048; // meters

    CannonSimulation cannonSimulation = CannonSimulation(
            totalGenerations, maxPopulation, childrenPerGen,
            targetDistance, maxBoreLength, maxBoreWidth, maxGunPowderMass,
            maxAngle, maxPlatformHeight, mutationChance, Gravity::EARTH,
            printEveryNthGeneration);

    // run the simulation
    cannonSimulation.simulate();
}

void livingStringTest() {
    LivingStringSimulation livingStringSimulation = LivingStringSimulation(
            "Hello World, Welcome to Genetic Programming! :D",
            10, 22, 50, 200);
    livingStringSimulation.simulate();
}

int main() {
    // sets the random seed
    srand((unsigned int) time(NULL));

    // TurtleBotSimulation(int totalGenerations, int childrenPerGeneration, double mutationChance,
    // int printEveryNthGeneration, int maxPopulation, int brainSize, Direction startDirection,
    //        TurtleBotMap turtleBotMap, float outOfBoundsPenalty, float goalReward);

    int totalGenerations = 10000;
    int childrenPerGeneration = 20;
    double mutationChance = 5;
    int printEveryNthGeneration = 1000;
    int maxPopulation = 100;
    int brainSize = 25;
    Direction startDirection = UP;

    vector<Point> goals;
    goals.push_back(Point(0, 3));
    goals.push_back(Point(1, 4));
    goals.push_back(Point(1, 0));
    goals.push_back(Point(3, 0));
    goals.push_back(Point(4, 2));

    TurtleBotMap turtleBotMap = TurtleBotMap(4, 4, goals, Point(0,0), Point(2,2));

    float outOfBoundsPenalty = 100;
    float goalReward = 50;
    float actionCost = 1;
    float finishOnEndReward = 10;
    float finishOffEndPenalty = 1000;
    float outOfActionsPenalty = 1000;

    TurtleBotSimulation turtleBotSimulation = TurtleBotSimulation(totalGenerations, childrenPerGeneration,
                                                                  mutationChance, printEveryNthGeneration,
                                                                  maxPopulation, brainSize, startDirection,
                                                                  turtleBotMap, outOfBoundsPenalty, goalReward,
                                                                  actionCost, finishOnEndReward, finishOffEndPenalty,
                                                                  outOfActionsPenalty);

    turtleBotSimulation.simulate();
}

