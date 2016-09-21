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
    TurtleBotMap();
    TurtleBotMap(int maxX, int maxY, vector<Point> goals, Point start, Point end);

    int getMaxX() const;

    int getMaxY() const;

    const vector<Point> getGoals() const;

    const Point getStart() const;

    const Point getEnd() const;
};
