#pragma once

#include "Animal.h"
#include "Point.h"
#include "TurtleBotMap.h"

enum Direction {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
};

enum TurtleBotAction {
    A_MOVE = 0,
    A_TURN_RIGHT = 1,
    A_TURN_LEFT = 2,
    A_FINISH = 3
    //A_DETECT
};

class TurtleBot : public Animal{
private:
    Point position = Point();
    Direction direction = Direction::UP;

public:
    vector<TurtleBotAction> brain;
    TurtleBot();
    TurtleBot(vector<TurtleBotAction> brain, Point position, Direction direction);
    void Move();
    void TurnRight();
    void TurnLeft();
    // TODO: implement logic into turtle bot brains
    void Detect(TurtleBotMap turtleBotMap);

    const Point &getPosition() const;

    Direction getDirection() const;

    void setPosition(const Point &position);

    void setDirection(Direction direction);
};
