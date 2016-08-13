#ifndef GENETICHELLOWORLD_ANIMAL_H
#define GENETICHELLOWORLD_ANIMAL_H

class Animal {
public:
    double fitnessValue;
    virtual void toString();
    Animal();
};

inline bool operator< (const Animal& lhs, const Animal& rhs){
    return lhs.fitnessValue < rhs.fitnessValue;
}

#endif


