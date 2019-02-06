//#include <stdio.h>
#include <iostream> // cout
#include <fstream> // argv[1]
#include <sstream> // stringstream
#include <vector> // vector
#include "instruction.h" // "instruction" method

using namespace std;

void printInstruction(string);

int main(int argc, char *argv[]) {
    // Reads in input .obj file, and determine if file exists.
    ifstream inFile(argv[1]);
    
    if(!inFile) {
        printf("%s%s\n", "Unable to open file ", argv[1]);
        exit(1);
    }

    string strInput;
    
    //Reads file line by line, stores line into "strInput"
    while(getline(inFile, strInput)) {

        // Partitions line into string, and pushes into vector "data".
        stringstream ss(strInput);
        string word;
        vector<std::string> data;

        while(ss >> word)
            data.push_back(word);
        
        // For addresses without opcode
        if(data.size() == 1) {
            cout << data[0] << '\n';
            continue;
        }

        // Here, data[0] := address and data[1] := opcode.
        // Opcode is passed to "instruction" method. 
        else {
            cout << data[0] << ' ';
            printInstruction(data[1]);
            cout << '\n';
        }
            
    }

    return 0;
}

