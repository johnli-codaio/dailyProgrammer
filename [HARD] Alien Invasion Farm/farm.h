#ifndef FARM_H_
#define FARM_H_

#include <vector>
#include <string>

struct Square {
    int x;
    int y;
    int sideLength;
};

class Farm {
    public:    
        Farm(int dimension);
        ~Farm();

        void setPlot(int x, int y, char farmPlot);
        char getPlot(int x, int y);

        void setCell(int x, int y, int size);
        int getCell(int x, int y);
        void setDropships(Square square);
        Square findLargestSquare();

        void populateTable();
        void printTable();
        void printFarm();

     private:
        int dimension;
        char* grid;
        int* memoizeTable;
};
#endif //FARM_H_