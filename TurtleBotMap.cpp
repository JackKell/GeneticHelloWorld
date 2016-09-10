#include "TurtleBotMap.h"

TurtleBotMap::TurtleBotMap(int maxX, int maxY, vector<Point> goals, Point start, Point end) {
    this->maxX = maxX;
    this->maxY = maxY;
    this->goals = goals;
    this->start = start;
    this->end = end;
}
