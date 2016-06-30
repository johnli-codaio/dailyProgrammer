#include "farm.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void parse(string fileName) {
    ifstream inFile(fileName);
    string line;
    int lineNum = 0;
    // Dimension size;
    getline(inFile, line);

    Farm farm(stoi(line));

    while(getline(inFile, line)) {
        for(int c = 0; c < line.length(); c++) {
            char plotChar = line[c];
            farm.setPlot(c, lineNum, plotChar);
        }
        lineNum++;
    }
    farm.printFarm();
    farm.populateTable();

    Square square = farm.findLargestSquare();
    farm.printTable();
    farm.setDropships(square);
    farm.printFarm();
    cout << square.sideLength * square.sideLength << " dropships!" << endl;
    return;
}

int main(int argc, char** argv) {
    string fileName = argv[1];
    parse(fileName);

    return 0;
}