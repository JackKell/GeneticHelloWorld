#include <string>

using std::string;

class Animal {
public:
    string dna;
    int fitnessValue;

    Animal(string dna = "", int fitnessValue = 0);
    ~Animal();
};

inline bool operator< (const Animal& lhs, const Animal& rhs){
    return lhs.fitnessValue < rhs.fitnessValue;
}


