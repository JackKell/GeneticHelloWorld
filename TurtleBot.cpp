#include "TurtleBot.h"

TurtleBot::TurtleBot(Point position, Direction direction) {
    this->position = position;
    this->direction = direction;
}

void TurtleBot::Move() {
    switch (direction) {
        case UP:
            position.incrementY();
            break;
        case RIGHT:
            position.incrementX();
            break;
        case DOWN:
            position.decrementY();
            break;
        case LEFT:
            position.decrementX();
            break;
    }
}

void TurtleBot::TurnRight() {
    direction = Direction((direction + 1) % 4);
}

void TurtleBot::TurnLeft() {
    direction = Direction((direction + 3) % 4);
}
