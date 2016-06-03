#include "grid.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

void placeMirrors(string fileName, Grid &grid) {
    ifstream inputFile(fileName);
    string line;

    for (int row = 1; row < 14; row++) {
        getline(inputFile, line);
        for (unsigned int col = 0; col < line.length(); col++) {
            if (line[col] == '/' || 
                line[col] == '\\') {
                grid.setMirror(row, col + 1, line[col]);
            }
        }
    }

    // Getting the input ready.
    getline(inputFile, line);
    grid.setString(line);
}

int main(int argc, char** argv) {
    Grid grid;

    string fileName = argv[1];
    placeMirrors(fileName, grid);

    string output = grid.decrypt();
    cout << output << endl;
    return 0;
}
