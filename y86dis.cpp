#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
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

    string strInput;

    while(std::getline(inFile, strInput)){
        std::stringstream ss(strInput);
        std::string word;
        std::vector<std::string> data;

        while(ss >> word)
            data.push_back(word);
        
        if(data.size() == 1){
            cout << data[0] << '\n';
            continue;
        }

        else{
            cout << data[0] << ' ';
            instruction(data[1]);
            cout << '\n';
        }
            
    }

    return 0;
}

