#include "TurtleBotSimulation.h"
#include <iostream>

using std::cout;
using std::endl;
using std::find;

TurtleBotSimulation::TurtleBotSimulation(int totalGenerations, int childrenPerGeneration, double mutationChance,
                                         int printEveryNthGeneration, int maxPopulation, int brainSize, Direction startDirection,
                                         TurtleBotMap turtleBotMap, float outOfBoundsPenalty, float goalReward, float actionCost,
                                         float finishOnEndReward, float finishOffEndReward, float outOfActionsPenalty)
        : Simulation(maxPopulation, childrenPerGeneration, mutationChance, printEveryNthGeneration) {
    this->brainSize = brainSize;
    this->startDirection = startDirection;
    this->turtleBotMap = turtleBotMap;
    this->outOfBoundsPenalty = outOfBoundsPenalty;
    this->goalReward = goalReward;
    this->totalGenerations = totalGenerations;
    this->actionCost = actionCost;
    this->finishOnEndReward = finishOnEndReward;
    this->finishOffEndPenalty = finishOffEndReward;
    this->outOfActionsPenalty = outOfActionsPenalty;
}

TurtleBot TurtleBotSimulation::createRandomIndividual() {
    vector<TurtleBotAction> brain;
    for(int i = 0; i < brainSize; i++) {
        brain.push_back(static_cast<TurtleBotAction>(rand() % 4));
    }
    return TurtleBot(brain, turtleBotMap.getStart(), startDirection);
}

TurtleBot TurtleBotSimulation::breed(TurtleBot turtleBot1, TurtleBot turtleBot2) {
    vector<TurtleBotAction> brain1 = turtleBot1.brain;
    vector<TurtleBotAction> brain2 = turtleBot2.brain;
    vector<TurtleBotAction> newBrain;

    int randomIndex = rand() % brainSize;
    for (unsigned int i = 0; i < brainSize; i++) {
        if (i < randomIndex) {
            newBrain.push_back(brain1.at(i));
        } else {
            newBrain.push_back(brain2.at(i));
        }
    }

    TurtleBot newTurtleBot = TurtleBot(newBrain, turtleBotMap.getStart(), startDirection);
    if (randomDouble(100) < mutationChance) {
        mutate(newTurtleBot);
    }

    fitnessTest(newTurtleBot);

    return newTurtleBot;
}

float TurtleBotSimulation::testSimilarity(TurtleBot turtleBot1, TurtleBot turtleBot2) {
    int similarityScore = 0;
    vector<TurtleBotAction> turtleBrain1 = turtleBot1.brain;
    vector<TurtleBotAction> turtleBrain2 = turtleBot2.brain;
    for (unsigned int i = 0; i < brainSize; i++) {
        if(turtleBrain1.at(i) == turtleBrain2.at(i)) {
            similarityScore++;
        }
    }
    return similarityScore;
}

void TurtleBotSimulation::mutate(TurtleBot &turtleBot) {
    const unsigned int randomIndex = (unsigned int) (rand() % brainSize);
    turtleBot.brain.at(randomIndex) = static_cast<TurtleBotAction>(rand() % 4);
}

void TurtleBotSimulation::fitnessTest(TurtleBot &turtleBot) {
    float fitnessScore = 0;
    turtleBot.setDirection(UP);
    turtleBot.setPosition(turtleBotMap.getStart());
    vector<Point> currentGoals = turtleBotMap.getGoals();
    vector<TurtleBotAction> turtleBrain = turtleBot.brain;
    for (unsigned int i = 0; i < brainSize; i++) {
        TurtleBotAction currentBotAction = turtleBrain.at(i);
        switch (currentBotAction) {
            case A_MOVE:
                turtleBot.Move();
                // If the turtle bot goes out of bounds its fitness score is reduced and the simulation ends for that turtle bot
                if (isOutOfBounds(turtleBot)) {
                    fitnessScore -= outOfBoundsPenalty;
                    turtleBot.fitnessValue = fitnessScore;
                    return;
                }
                // Check the points to see if the turtle bot has reached a goal point
                for (Point &goalPoint : currentGoals) {
                    // If the turtle bot has reached a goal point reward it and remove the point
                    if (turtleBot.getPosition() == goalPoint) {
                        auto it = find(currentGoals.begin(), currentGoals.end(), goalPoint);
                        if (it != currentGoals.end()) {
                            fitnessScore += goalReward;
                            currentGoals.erase(it);
                        }
                    }
                }
                break;
            case A_TURN_LEFT:
                turtleBot.TurnLeft();
                break;
            case A_TURN_RIGHT:
                turtleBot.TurnRight();
                break;
            case A_FINISH:
                if (turtleBot.getPosition() == turtleBotMap.getEnd()) {
                    fitnessScore += finishOnEndReward;
                } else {
                    fitnessScore -= finishOffEndPenalty;
                }
                turtleBot.fitnessValue = fitnessScore;
                return;
            default:
                cout << "It seems as though you created a new turtle bot action and forgot to put it in the switch case." << endl;
        }
        fitnessScore -= actionCost;
    }
    fitnessScore -= outOfActionsPenalty;
    turtleBot.fitnessValue = fitnessScore;
}

bool TurtleBotSimulation::reachedGoal() {
    return totalGenerations <= currentGeneration;
}

void TurtleBotSimulation::printPopulation() {
    cout << "Generation: " << currentGeneration << endl;
    const string titleSeparator = "  |  ";
    const string separator = " | ";
    cout << "R " << titleSeparator
         << "FV" << titleSeparator
         << "Brain" << endl;
    for (unsigned int i = 0; i < population.size(); i++) {
        TurtleBot turtleBot = population.at(i);
        string brain = "";
        for (TurtleBotAction turtleBotAction : turtleBot.brain) {
            switch (turtleBotAction) {
                case A_MOVE:
                    brain += "M";
                    break;
                case A_TURN_LEFT:
                    brain += "L";
                    break;
                case A_TURN_RIGHT:
                    brain += "R";
                    break;
                case A_FINISH:
                    brain += "F";
                    break;
            }
        }
        cout << (i + 1) << separator
             << turtleBot.fitnessValue << separator
             << brain << endl;
    }
}

bool TurtleBotSimulation::isOutOfBounds(TurtleBot turtleBot) {
    Point turtleBotPosition = turtleBot.getPosition();
    if (turtleBotPosition.getX() < 0 || turtleBotPosition.getX() > turtleBotMap.getMaxX()) {
        return true;
    } else {
        return turtleBotPosition.getY() < 0 || turtleBotPosition.getY() > turtleBotMap.getMaxY();
    }
}

void TurtleBotSimulation::sortPopulation() {
    sort(population.rbegin(), population.rend());
}

void TurtleBotSimulation::addChildrenToPopulation() {
     Simulation::addChildrenToPopulation();

//    for (int i = 0; i < childrenPerGeneration; i++) {
//        const int randomIndex = rand() % population.size();
//
//        // Set the turtle bot to a random elite turtle bot
//        const TurtleBot turtleBot1 = population.at((unsigned int) randomIndex);
//        // Set the turtle bot to a random individual bot for safety reasons
//        TurtleBot turtleBot2 = getRandomIndividual();
//        float bestSimScore = 0;
//        for (unsigned int currentIndex = 0; currentIndex < population.size(); currentIndex++) {
//            if (randomIndex != currentIndex) {
//                TurtleBot currentTurtleBot = population.at(currentIndex);
//                float currentSim = testSimilarity(turtleBot1, currentTurtleBot);
//                if (currentSim > bestSimScore) {
//                    bestSimScore = currentSim;
//                    turtleBot2 = currentTurtleBot;
//                }
//            }
//        }
//
//        TurtleBot turtleBot = breed(turtleBot1, turtleBot2);
//        population.push_back(turtleBot);
//    }
}
