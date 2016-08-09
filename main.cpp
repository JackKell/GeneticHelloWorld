#include <iostream>
#include <cmath>
#include <vector>
#include <c++/ctime>
#include <algorithm>
#include <functional>
#include <array>

#include "Animal.h"

using std::string;
using std::cout;
using std::abs;
using std::pow;
using std::endl;
using std::vector;
using std::sort;


int fitnessTest(string source, string target) {
    int fitnessValue = 0;
    for(int i = 0; i < source.length(); i++) {
        char sourceChar = source[i];
        char targetChar = target[i];
        int delta = (int) abs(sourceChar - targetChar);
        fitnessValue += delta;
    }
    return fitnessValue;
}

string mutate(string source) {
    int randomIndex = (int) (rand() % (source.length()));
    source[randomIndex] = (char) (source[randomIndex] + ((rand() % 51) - 25));
    return source;
}

Animal mutate(Animal mother, Animal father) {
    int dnaLength = (int) mother.dna.length();
    int randomIndex = rand() % dnaLength;
    string childDna = mother.dna.substr(0, randomIndex) + father.dna.substr(randomIndex, dnaLength);

    childDna = mutate(childDna);
    return Animal(childDna);
}

string generateRandomString(int length) {
    string randomString = "";
    for (int i = 0; i < length; i++) {
        int randomNum = (rand() % (127 - 32)) + 32;
        char randomChar = (char) randomNum;
        randomString += randomChar;
    }
    return randomString;
}

void printAnimals(vector<Animal> animals) {
    cout << "Fitness Value\t|\tDNA" << endl;
    for (int i = 0; i < animals.size(); i++) {
        Animal currentAnimal = animals[i];
        cout << currentAnimal.fitnessValue << "\t\t|\t" << currentAnimal.dna << endl;
    }
}

Animal getRandomAnimal(vector<Animal> animals) {
    return animals[rand() % animals.size()];
}


void firstSim() {
    string target = "Hello everyone, welcome to the party ! :D This is an example of a genetic program...";
    string source = generateRandomString(target.length());

    int fitnessValue = fitnessTest(source, target);
    int generation = 0;

    cout << "Target: " << target << endl;
    cout << "Gen: " << generation << " | " << "Value: " << fitnessValue << " | " << source << endl;
    int totalIterations = 0;
    int generationalIteration = 0;
    while (fitnessValue != 0) {
        string mutatedSource = mutate(source);
        int mutatedFitnessValue = fitnessTest(mutatedSource, target);
        if (fitnessValue > mutatedFitnessValue) {
            source = mutatedSource;
            fitnessValue = mutatedFitnessValue;
            generation++;
            generationalIteration++;
            cout << "Gen: " << generation << " | " << "Value: " << fitnessValue << " | " << source << endl;
            cout << "\t- Taking " << generationalIteration << " generational iterations" << endl;
            generationalIteration = 0;
        } else {
            generationalIteration++;
        }
        totalIterations++;
    }
    cout << "That took a total of " << totalIterations << " iterations";
}

void secondSim() {
    string target = "Hello everyone, welcome to the party ! :D This is an example of a genetic program...";
    cout << "The target is: " << target << endl;
    int Population = 30;
    int childrenPerGeneration = 5;
    int DnaLength = (int) target.length();
    vector<Animal> animals;
    int generation = 0;
    // Create generation 0
    for (int i = 0; Population > i; i++) {
        string dna = generateRandomString(DnaLength);
        Animal newAnimal = Animal(dna, fitnessTest(dna, target));
        animals.push_back(newAnimal);
    }
    sort(animals.begin(), animals.end());
    cout << "Generation: " << generation << endl;
    printAnimals(animals);
    while (animals.front().fitnessValue != 0) {
        for (int i = 0; i < childrenPerGeneration; i++) {
            Animal newChild = mutate(getRandomAnimal(animals), getRandomAnimal(animals));
            newChild.fitnessValue = fitnessTest(newChild.dna, target);
            animals.push_back(newChild);
        }
        sort(animals.begin(), animals.end());
        for (int i = 0; i < childrenPerGeneration; i++) {
            animals.pop_back();
        }
        generation++;
        if (generation % 500 == 0) {
            cout << "Generation: " << generation << endl;
            printAnimals(animals);
        }
    }
    cout << "Generation: " << generation << endl;
    printAnimals(animals);

}

int main() {
    srand((unsigned int) (int)time(0));
    //firstSim();
    secondSim();
}

