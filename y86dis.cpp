// To generate mnemonics...
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib> // for exit()
#include <sstream>


std::string extractInstr(const std::string& input)
{
    using namespace std;
    string high2 = input.substr(0,2);
    
    string fin = "";
    int count = 0;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] != ' ') {
            count++;
        }
    }

    if (count == 16) {
        fin = ".quad";
    }
    
    
    else if (high2.compare("  ") == 0) {
        fin = "";
    }
    else if (high2.compare("00") == 0 ) {
        fin = "halt";
    }
    else if (high2.compare("10") == 0) {
        fin = "nop";
    }
    else if (high2.compare("20") == 0) {
        fin = "rrmovq";
    }
    else if (high2.compare("30") == 0) {
        fin = "irmovq";
    }
    else if (high2.compare("40") == 0) {
        fin = "rmmovq";
    }
    else if (high2.compare("50") == 0) {
        fin = "mrmovq";
    }
    else if (high2.compare("60") == 0) {
        fin = "addq";
    }
    else if (high2.compare("61") == 0) {
        fin = "subq";
    }
    else if (high2.compare("62") == 0) {
        fin = "andq";
    }
    else if (high2.compare("63") == 0) {
        fin = "xorq";
    }
    else if (high2.compare("70") == 0) {
        fin = "jmp";
    }
    else if (high2.compare("71") == 0) {
        fin = "jle";
    }
    else if (high2.compare("72") == 0) {
        fin = "jl";
    }
    else if (high2.compare("73") == 0) {
        fin = "je";
    }
    else if (high2.compare("74") == 0) {
        fin = "jne";
    }
    else if (high2.compare("75") == 0) {
        fin = "jge";
    }
    else if (high2.compare("76") == 0) {
        fin = "jg";
    }

    else if (high2.compare("21") == 0) {
        fin = "cmovle";
    }

    else if (high2.compare("22") == 0) {
        fin = "cmovl";
    }

    else if (high2.compare("23") == 0) {
        fin = "comve";
    }

    else if (high2.compare("24") == 0) {
        fin = "cmovne";
    }

    else if (high2.compare("25") == 0) {
        fin = "cmovge";
    }

    else if (high2.compare("26") == 0) {
        fin = "cmovg";
    }

    else if (high2.compare("80") == 0) {
        fin = "call";
    }

    else if (high2.compare("90") == 0) {
        fin = "ret";
    }

    else if (high2.compare("a0") == 0) {
        fin = "pushq";
    }

    else if (high2.compare("b0") == 0) {
        fin = "popq";
    }
    else {
        fin = "illegal op";
    }
    return fin;
}

std::string convertReg(const std::string& input) {
    std::string output;
    if (input.compare("0") == 0) {
        output = "%rax";
    }
    if (input.compare("1") == 0) {
        output = "%rcx";
    }
    if (input.compare("2") == 0) {
        output = "%rdx";
    }
    if (input.compare("3") == 0) {
        output = "%rbx";
    }
    if (input.compare("4") == 0) {
        output = "%rsp";
    }
    if (input.compare("5") == 0) {
        output = "%rbp";
    }
    if (input.compare("6") == 0) {
        output = "%rsi";
    }
    if (input.compare("7") == 0) {
        output = "%rdi";
    }
    if (input.compare("8") == 0) {
        output = "%r8";
    }
    if (input.compare("9") == 0) {
        output = "%r9";
    }
    if (input.compare("a") == 0) {
        output = "%r10";
    }
    if (input.compare("b") == 0) {
        output = "%r11";
    }
    if (input.compare("c") == 0) {
        output = "%r12";
    }
    if (input.compare("d") == 0) {
        output = "%r13";
    }
    if (input.compare("e") == 0) {
        output = "%r14";
    }
    if (input.compare("f") == 0) {
        output = "RNONE";
    }
    return output;
}


std::string* extractRegs(const std::string& input) {
    std::string highest = input.substr(0,1);
    std::string* output = new std::string[2];    

    if (highest.compare("2") == 0 ||
        highest.compare("4") == 0 ||
        highest.compare("5") == 0 || 
        highest.compare("6") == 0) {
        output[0] = convertReg(input.substr(2,1));
        output[1] = convertReg(input.substr(3,1));        
    }
    else if (highest.compare("a") == 0 ||
             highest.compare("b") == 0) {
        output[0] = convertReg(input.substr(2,1));
    }
    else if (highest.compare("3") == 0) {
        output[0] = convertReg(input.substr(3,1));
    }

    return output;
}

std::string littleToBigEndian(const std::string& input, bool isQuad) {
    std::string output;
    std::string highest = input.substr(0,1);
    if (isQuad) {
        std::string littleEnd = input.substr(0, 16);
        for (int i = 8; i > 0; i--) {
            int start = (i - 1) * 2;
            int length = 2;
            output += littleEnd.substr(start, length);
        }
    }
    else if (highest.compare("3") == 0 ||
             highest.compare("4") == 0 ||
             highest.compare("5") == 0) {
        std::string littleEnd = input.substr(4, 16);
        for (int i = 8; i > 0; i--) {
            int start = (i - 1) * 2;
            int length = 2;
            output += littleEnd.substr(start, length);
        }
    }
    else if (highest.compare("7") == 0 ||
             highest.compare("8") == 0) {
        std::string littleEnd = input.substr(2, 16);
        for (int i = 8; i > 0; i--) {
            int start = (i - 1) * 2;
            int length = 2;
            output += littleEnd.substr(start, length);
        }
    }
    if (highest.compare("3") == 0 &&
        input.substr(8, 2) == "ff") {
        
    }
    else if (!isQuad) {
        long hexRep = std::strtoll(output.c_str(), NULL, 16);
        std::stringstream converted;
        converted << std::hex << hexRep;
        return "0x" + converted.str();
    }
    return "0x" + output;  
}

std::string buildMnemonic(const std::string& addr,
                          const std::string& instr,
                          std::string regs[2],
                          const std::string& bigEndWord,
                          const std::string& initial) {
    std::string output;
    std::string highest = initial.substr(0,1);
    
    output = addr;
 
    int count = 0;
    for (int i = 0; i < initial.length(); i++) {
        if (initial[i] != ' ') {
            count++;
        }
    }
    if (count == 16) {
        output += ".quad ";
        output += littleToBigEndian(initial, true);
    }
    else {
        output += instr;

        if (highest.compare("2") == 0 ||
            highest.compare("6") == 0) {
            output += " ";
            output += regs[0];
            output += ", ";
            output += regs[1];
        }
        else if (highest.compare("a") == 0 ||
                 highest.compare("b") == 0) {
            output += " ";
            output += regs[0];
        }
        else if (highest.compare("3") == 0) {
            output += " $";
            output += bigEndWord;
            output += ", ";
            output += regs[0];
        }
        else if (highest.compare("4") == 0) {
            output += " ";
            output += regs[0];
            output += ", $";
            output += bigEndWord;
            output += "(";
            output += regs[1];
            output += ")";
        }
        else if (highest.compare("5") == 0) {
            output += " $";
            output += bigEndWord;
            output += "(";
            output += regs[1];
            output += "), ";
            output += regs[0];
        }
        else if (highest.compare("7") == 0 ||
                 highest.compare("8") == 0) {
            output += " ";
            output += bigEndWord;
        } 
    }
    return output;
}

int main(int argc, char *argv[]){
    using namespace std;
    // Reads in input .obj file, and determine if file exists.
    ifstream inFile(argv[1]);
    if(!inFile){
        printf("%s%s\n", "Unable to open file ", argv[1]);
        exit(1);
    }

    stringstream ss;

    string strInput;

    string word; 
    
    while (inFile)
    {
        std::string strInput;
        getline(inFile, strInput);
        if(!inFile.eof()) {
            string addr = strInput.substr(0, 6);
            strInput = strInput.substr(7, 20);
            string instruct = extractInstr(strInput);
            string* regs = extractRegs(strInput);
            string bigEnd = littleToBigEndian(strInput, false);
            string finalMnemonic = buildMnemonic(addr, instruct, regs, bigEnd, strInput);
            cout << finalMnemonic << endl;
        }

    }

    return 0;


}



/*int main()
{
    using namespace std;
 
    ifstream inf("prog1.obj");
 
    if (!inf)
    {
        cerr << "Uh oh, Sample.dat could not be opened for reading!" << endl;
        exit(1);
    }
 
    while (inf)
    {
        std::string strInput;
        getline(inf, strInput);
        if(!inf.eof()) {
            string addr = strInput.substr(0, 6);
            strInput = strInput.substr(7, 20);
            string instruct = extractInstr(strInput);    
            string* regs = extractRegs(strInput);
            string bigEnd = littleToBigEndian(strInput);
            string finalMnemonic = buildMnemonic(addr, instruct, regs, bigEnd, strInput);
            cout << finalMnemonic << endl;
        }
 
    }
     
    return 0;
    
}
*/
