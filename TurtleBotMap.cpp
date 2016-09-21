#include "TurtleBotMap.h"

TurtleBotMap::TurtleBotMap() {
    this->maxX = 0;
    this->maxY = 0;
    this->start = Point();
    this->end = Point();
}

TurtleBotMap::TurtleBotMap(int maxX, int maxY, vector<Point> goals, Point start, Point end) {
    this->maxX = maxX;
    this->maxY = maxY;
    this->goals = goals;
    this->start = start;
    this->end = end;
}

int TurtleBotMap::getMaxX() const {
    return maxX;
}

int TurtleBotMap::getMaxY() const {
    return maxY;
}

const vector<Point> TurtleBotMap::getGoals() const {
    return goals;
}

const Point TurtleBotMap::getStart() const {
    return start;
}

const Point TurtleBotMap::getEnd() const {
    return end;
}
