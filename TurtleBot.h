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

enum TurtleBotActions {
    A_MOVE,
    A_RIGHT,
    A_LEFT,

};

class TurtleBot : public Animal{
private:
    Point position = Point();
    Direction direction = Direction::UP;
public:
    TurtleBot(Point position, Direction direction);
    void Move();
    void TurnRight();
    void TurnLeft();
    void Detect(TurtleBotMap turtleBotMap);
};
