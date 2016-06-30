#include "farm.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

Farm::Farm(int dim) {
    this->dimension = dim;
    this->grid = new char[dim * dim];
    this->memoizeTable = new int[dim * dim];
    for(int i = 0; i < dim * dim; i++) {
        this->memoizeTable[i] = 0;
    }
}

Farm::~Farm() {
    delete[] this->grid;
    delete[] this->memoizeTable;
}

void Farm::setPlot(int x, int y, char farmPlot) {
    this->grid[y * dimension + x] = farmPlot;
}

char Farm::getPlot(int x, int y) {
    return this->grid[y * dimension + x];
}

void Farm::setCell(int x, int y, int size) {
    this->memoizeTable[y * dimension + x] = size;
}

int Farm::getCell(int x, int y) {
    return this->memoizeTable[y * dimension + x];
}

void Farm::populateTable() {
    // Going from bottom right to top left.
    for(int y = this->dimension - 1; y >= 0; y--) {
        for (int x = this->dimension - 1; x >= 0; x--) {
            // X's cannot be squares
            if(this->getPlot(x, y) == 'X')
                this->setCell(x, y, 0);

            // Start edges cannot be greater than 1.
            else if(x == this->dimension - 1 || y == this->dimension - 1)
                this->setCell(x, y, 1);

            else if(x < this->dimension - 1 && y < this->dimension - 1) {
                if(this->getPlot(x + 1, y + 1) == 'X')
                    this->setCell(x, y, 1);

                else if(this->getCell(x + 1, y) != this->getCell(x, y + 1))
                    this->setCell(x, y, 1 +
                        min(this->getCell(x + 1, y), this->getCell(x, y + 1)));

                else
                    this->setCell(x, y,
                        min(this->getCell(x + 1, y), this->getCell(x + 1, y + 1)) + 1);
            }
        }
    }
}

Square Farm::findLargestSquare() {
    Square square;
    square.x = 0;
    square.y = 0;
    square.sideLength = 0;

    for(int y = 0; y < this->dimension - 1; y++) {
        for(int x = 0; x < this->dimension - 1; x++) {
            int currSize = this->getCell(x, y);
            if(currSize > square.sideLength) {
                square.x = x;
                square.y = y;
                square.sideLength = currSize;
            }
        }
    }

    return square;
}

void Farm::printTable() {
    for(int y = 0; y < this->dimension; y++) {
        for(int x = 0; x < this->dimension; x++) {
            cout << this->getCell(x, y);
        }
        cout << endl;
    }
}

void Farm::printFarm() {
    for(int y = 0; y < this->dimension; y++) {
        for(int x = 0; x < this->dimension; x++) {
            cout << this->getPlot(x, y);
        }
        cout << endl;
    }
}

// Just printing first instance of dropships.
void Farm::setDropships(Square square) {
    int startX = square.x;
    int startY = square.y;
    int dimension = square.sideLength;

    for(int y = startY; y < startY + dimension; y++) {
        for(int x = startX; x < startX + dimension; x++) {
            this->setPlot(x, y, 'O');
        }
    }
}