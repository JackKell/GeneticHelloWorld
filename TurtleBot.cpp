#include "TurtleBot.h"

TurtleBot::TurtleBot() {
    this->position = Point();
    this->direction = UP;
}

TurtleBot::TurtleBot(vector<TurtleBotAction> brain, Point position, Direction direction) {
    this->brain = brain;
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

void TurtleBot::Detect(TurtleBotMap turtleBotMap) {

}

const Point &TurtleBot::getPosition() const {
    return position;
}

Direction TurtleBot::getDirection() const {
    return direction;

}

void TurtleBot::setPosition(const Point &position) {
    this->position = position;
}

void TurtleBot::setDirection(Direction direction) {
    this->direction = direction;
}
