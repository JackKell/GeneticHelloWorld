#include "Point.h"

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

int Point::getX() const {
    return x;
}

void Point::setX(int x) {
    Point::x = x;
}

int Point::getY() const {
    return y;
}

void Point::setY(int y) {
    Point::y = y;
}

void Point::incrementX(int x) {
    Point::x = Point::x + x;
}

void Point::decrementX(int x) {
    Point::x = Point::x - x;
}

void Point::incrementY(int y) {
    Point::y = Point::y + y;
}

void Point::decrementY(int y) {
    Point::y = Point::y - y;
}
