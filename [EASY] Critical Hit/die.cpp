#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Recursively calculate probability for killing a monster.
double calculateProb(int side, int hp) {
    if (hp <= side) {
        return (side + 1 - hp) / double(side);
    }
    else {
        return (1.0 / side) * calculateProb(side, hp - side);
    }
}

// Mean value for one iteration of dice rolling...
double meanValueDice(int iter, int side) {
    double meanValue = 0;

    for(int i = 1; i < side; i++) {
        meanValue += (1.0 / side) * ((iter * side) + i);
    }
    return meanValue;
}

int main(int argc, char* argv[]) {
    int side = stoi(argv[1]);
    int hp = stoi(argv[2]);
    double meanValue = 0;

    // Calculating probabilities here.
    double probability = calculateProb(side, hp);
    cout << probability << endl;

    // Calculating mean value for any attack here, based on dice size.
    for(int iter = 0; iter < 3000; iter++) {
        meanValue += pow((1.0 / side), iter) * meanValueDice(iter, side);
    }

    cout << meanValue << endl;
    return 0;
}
