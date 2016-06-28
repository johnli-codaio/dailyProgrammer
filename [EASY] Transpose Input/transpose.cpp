#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void printTranspose(vector<string> inputStrings, unsigned int maxLength) {
    for(unsigned int i = 0; i < maxLength; i++) {
        for(auto& line: inputStrings) {
            if(line.length() <= i) cout << " ";
            else cout << line[i];
        }
        cout << endl;
    }
}

void parseFile(string fileName) {
    ifstream inFile(fileName);
    string line;
    vector<string> lines;
    unsigned int maxLength = 0;

    while(getline(inFile, line)) {
        lines.push_back(line);
        if (line.length() > maxLength) maxLength = line.length(); 
    }
    printTranspose(lines, maxLength);
}

int main(int argc, char** argv) {
    string fileName = argv[1];
    parseFile(fileName);
}