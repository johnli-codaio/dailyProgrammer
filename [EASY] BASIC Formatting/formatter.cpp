#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <vector>

using namespace std;

void errorPrint(string misMatch, int lineNum) {
    if (misMatch == "FOR") {
        cerr << "Error: Mismatch between ENDIF and " << misMatch <<
        " on line " << lineNum << endl;
    }
    else {
        cerr << "Error: misMatch between NEXT and " << misMatch << 
        " on line " << lineNum << endl;
    }
}

void parse(string fileName) {
    ifstream inFile(fileName); 
    ofstream outFile("output.txt");

    string line; // each line received by getline()
    int numLines; 
    string tabDelim;

    // Used to match blocks with other blocks.
    vector<string> blocks;

    int numTabs = 0; // every block encounter increments this by one.

    getline(inFile, line); 
    numLines = stoi(line);

    getline(inFile, line); // <-- The space delimitation.
    tabDelim = line;

    for (int row = 0; row < numLines; row++) {
        getline(inFile, line);

        // Strip line from all leading white space.
        size_t startString = line.find_first_not_of(" \t");
        string parsedString = line.substr(startString);

        // Check to see if a block ends. If so, we move back
        // a few spaces.
        size_t foundNext = line.find("NEXT");
        size_t foundEndIf = line.find("ENDIF");

        // Error checking for correct blocks.
        // If the block head/end match, then we pop from stack.
        // Otherwise, we throw error.
        if (foundNext != string::npos ||
             foundEndIf != string::npos) {
            if (blocks.size() > 0) {
                if ((foundNext != string::npos && blocks.back() == "FOR") ||
                    (foundEndIf != string::npos && blocks.back() == "IF")) {
                    numTabs--;
                    blocks.pop_back();
                }
                else {
                    string misMatch = blocks.back();
                    errorPrint(misMatch, row + 1);
                    return;
                }
            }
            else {
                cerr << "Error: Extra ending block at line " << row << endl;
                return;
            }       
        }

        for (int blockNum = 0; blockNum < numTabs; blockNum++) {
            outFile << tabDelim;
        }

        outFile << parsedString << endl;

        size_t foundIf = line.find("IF ");
        size_t foundFor = line.find("FOR");


        if (foundIf != string::npos ||
            foundFor != string::npos) {
            numTabs++;

            // Populating the stack for matching purposes.
            if (foundIf != string::npos)
                blocks.push_back("IF");
            else 
                blocks.push_back("FOR");
        }
    }
    if (blocks.size() != 0) {
        cerr << "Error: did not close the ";
        for (auto i: blocks) {
            cerr << i << ", ";
        }
        cerr << "blocks in the input" << endl;
        return;
    }
}

int main(int argc, char* argv[]) {
    string fileName = argv[1];
    parse(fileName);

    return 0;
}