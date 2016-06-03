#ifndef GRID_H_
#define GRID_H_

#include <utility>
#include <map>
#include <string> 

using namespace std;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Grid {
    public:
        // Constructor
        Grid();

        // Destructor.
        ~Grid();

        // Accessors.

        // Going to be 1-indexed, since 0th row/col
        // and 14th row/col are occupied by letters.
        char getLocation(int row, int col) const;

        string getString() const;
        // Mutators

        // Going to be 1-indexed, since 0th row/col
        // and 14th row/col are occupied by letters.
        void setMirror(int row, int col, char type);

        void setString(string input);
        
        // Will explore all of the mirrors and search 
        // accordingly.
        char peek(char input);

        string decrypt();

    private:
        // Grid for the encryption.
        char* grid;

        // Map for Input Alphabet.
        map<char, pair<int, Direction> > inputAlph;

        string encryptString;
};

#endif // GRID_H_