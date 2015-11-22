#include <iostream>
#include <list>
#include <vector>
#include <string.h>
#include "Animal.h"

using std::cout;
using std::string;
using std::endl;
using std::list;
using std::vector;

string validChars = "0123456789!@#$%^&*ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

char GenerateRandomCharacter() {
    return validChars[rand() % validChars.length()];
}

string GenerateRandomString(int length) {
    if (length <= 0) {
        return "";
    }

    string randomString = "";

    for (int i = 0; i < length; i++) {
        randomString += GenerateRandomCharacter();
    }

    return randomString;
}

void SetFitnessScore(Animal &animal, string correctGene) {
    int score = 0;
    for (char currentAnimalGene : animal.GetGene()) {
        for (char currentCorrectGene : correctGene) {
            /*
            if (strcmp((const char *) currentAnimalGene, (const char *) currentCorrectGene)) {
                score++;
            }
            */
        }
    }
    animal.fitnessScore = score;
    return;
}

int HighestFitnessScore(vector<Animal> animals) {
    int highestFitnessScore = 0;
    for (Animal currentAnimal : animals) {
        if (currentAnimal.fitnessScore > highestFitnessScore) {
            highestFitnessScore = currentAnimal.fitnessScore;
        }
    }
    return highestFitnessScore;
}

int main() {
    cout << "Starting the Genetic Programming Example " << endl;
    string answerString = "hello World";

    long int lengthOfGene = answerString.length();
    int numberOfStartingAnimals = 100;
    vector<Animal> animals = {};

    // Create the random starting population
    for (int i = 0; i < numberOfStartingAnimals; i++) {
        Animal newAnimal = Animal(GenerateRandomString(lengthOfGene));
        animals.push_back(newAnimal);
    }

    /*
    // Loop through generations
    for (int currentAnimalIndex = 0; currentAnimalIndex < animals.size(); currentAnimalIndex++) {
        Animal currentAnimal = animals[currentAnimalIndex];

    }
     */

    return 0;
}

