#pragma once

#include <vector>
#include "Point.h"

using std::vector;

class TurtleBotMap {
private:
    int maxX;
    int maxY;
    vector<Point> goals;
    Point start;
    Point end;
public:
    TurtleBotMap(int maxX, int maxY, vector<Point> goals, Point start, Point end);
};
