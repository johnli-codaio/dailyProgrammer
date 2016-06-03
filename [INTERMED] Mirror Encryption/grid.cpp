#include "grid.h"

Grid::Grid() {
    // Populating the grid.
    this->grid = new char[15 * 15];

    // Setting everything to be '.'
    for (int i = 0; i < (15 * 15); i++) 
        this->grid[i] = '.';
    
    // Now, populating borders with letters.
    char topRow[13] = 
        {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm'};

    char leftCol[13] = 
        {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M'};

    char rightCol[13] = 
        {'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    char botRow[13] = 
        {'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    for (int col = 1; col < 14; col++) {
        this->grid[col] = topRow[col - 1];
        pair<int, Direction> topPair(col, DOWN);
        this->inputAlph[topRow[col - 1]] = topPair;

        this->grid[15 * 14 + col] = botRow[col - 1];
        pair<int, Direction> botPair(15 * 14 + col, UP);
        this->inputAlph[botRow[col - 1]] = botPair;
    }

    for (int row = 1; row < 14; row++) {
        this->grid[15 * row] = leftCol[row - 1];
        pair<int, Direction> leftPair(15 * row, RIGHT);
        this->inputAlph[leftCol[row - 1]] = leftPair;

        this->grid[15 * row + 14] = rightCol[row - 1];
        pair<int, Direction> rightPair(15 * row + 14, LEFT);
        this->inputAlph[rightCol[row - 1]] = rightPair;
    }
}

Grid::~Grid() {
    delete[] this->grid;
}

char Grid::getLocation(int row, int col) const {
    return this->grid[row * 15 + col];
}

void Grid::setMirror(int row, int col, char type) {
    this->grid[row * 15 + col] = type;
}

string Grid::getString() const {
    return this->encryptString;
}

void Grid::setString(string input) {
    this->encryptString = input;
}

char Grid::peek(char input) {
    int startLocation = this->inputAlph[input].first;
    Direction movement = this->inputAlph[input].second;
    while (true) {

        if (movement == UP)
            startLocation -= 15;
        else if (movement == DOWN)
            startLocation += 15;
        else if (movement == LEFT)
            startLocation -= 1;
        else if (movement == RIGHT)
            startLocation += 1;

        char output = this->grid[startLocation];

        if (output == '/') {

            if (movement == DOWN) movement = LEFT;
            else if (movement == UP) movement = RIGHT;
            else if (movement == LEFT) movement = DOWN;
            else if (movement == RIGHT) movement = UP;
        }
        
        else if (output == '\\') {

            if (movement == DOWN) movement = RIGHT;
            else if (movement == UP) movement = LEFT;
            else if (movement == LEFT) movement = UP;
            else if (movement == RIGHT) movement = DOWN;
        }

        else if (output == '.') continue;

        else {
            return output;
        }
    }

}

string Grid::decrypt() {
    string buf = "";
    for (unsigned int c = 0; c < this->encryptString.length(); c++) {
        char outputChar = this->peek(this->encryptString[c]);
        buf.push_back(outputChar);
    }
    return buf;
}