#pragma once

class Point {
private:
    int x;
    int y;
public:
    Point(int x = 0, int y = 0);

    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);
    void incrementX(int x = 1);
    void decrementX(int x = 1);
    void incrementY(int y = 1);
    void decrementY(int y = 1);
};

inline bool operator== (const Point& lhs, const Point& rhs){
    return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
}
