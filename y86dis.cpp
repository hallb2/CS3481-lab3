#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "instruction.h"

using namespace std;

void instruction(string);

int main(int argc, char *argv[]){
    // Reads in input .obj file, and determine if file exists.
    ifstream inFile(argv[1]);
    
    if(!inFile){
        printf("%s%s\n", "Unable to open file ", argv[1]);
        exit(1);
    }

    stringstream ss;

    string strInput;

    string word; 

    while(std::getline(inFile, strInput)){
        instruction(strInput);
        cout << "\n";
    }

    return 0;
}

