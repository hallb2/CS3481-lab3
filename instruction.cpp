#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "instruction.h"

std::string instruction(std::string s){
    
    // Initialize stringstream, and push address/instruction into vector "data"
    std::stringstream ss(s);
    std::string word;
    std::vector<std::string> data;

    while(ss >> word)
        data.push_back(word);

    // Declare mappings via "map"
    std::map <std::string, std::string> format;

    format["00"] = "halt";

    format["10"] = "nop";

    format["20"] = "rrmovq";
        
    format["21"] = "cmovle";
        
    format["22"] = "cmovl";
        
    format["23"] = "cmove";
        
    format["24"] = "cmovne";
        
    format["25"] = "cmovge";
        
    format["26"] = "cmovg";
    
    format["30"] = "irmovq";
    
    format["40"] = "rmmovq";

    format["50"] = "mrmovq";

    format["60"] = "addq";

    format["61"] = "subq";

    format["62"] = "andq";

    format["63"] = "xorq"; 

    format["70"] = "jmp";

    format["71"] = "jle";

    format["72"] = "jl";

    format["73"] = "je";

    format["74"] = "jne";

    format["75"] = "jge";

    format["76"] = "jg";
    
    format["80"] = "call";

    format["90"] = "ret";

    format["a0"] = "pushq";

    format["A0"] = "pushq";

    format["b0"] = "popq";

    format["B0"] = "popq";
    
    if(data[1][0] == '0' || data[1][0] == '1' || data[1][0] == '9')
        return data[0] + format[data[1].substr(0, 2)];
    
    else if(data[1][0] == '2' || data[1][0] == '4' || data[1][0] == '5' || data[1][0] == '6')
        return data[0] + format[data[1].substr(0, 2)] + registers(data[1][2]) + registers(data[1][3]);
   
    else if(data[1][0] == '3')
        return data[0] + format[data[1].substr(0, 2)] + offset(data[1].substr(4, data[1].length()));
    
    else
        return data[0] + format[data[1].substr(0, 2)];

}

std::string registers(char c){
    std::map <char, std::string> reg_num;

    reg_num['0'] = "ax";
    
    reg_num['1'] = "cx";

    reg_num['2'] = "dx";
    
    reg_num['3'] = "bx";
    
    reg_num['4'] = "sp";
    
    reg_num['5'] = "bp";
    
    reg_num['6'] = "si";
    
    reg_num['7'] = "di";
    
    reg_num['8'] = "8";
    
    reg_num['9'] = "9";

    reg_num['a'] = "10";
    
    reg_num['b'] = "11";
    
    reg_num['c'] = "12";

    reg_num['d'] = "13";

    reg_num['e'] = "14";

    return "%r" + reg_num[c];
}

std::string offset(std::string s){
    std::string t = "";
    
    for(int i = s.length() / 2; i >= 0; i--){
        t += s.substr(i*2, 2);
    }
    return t;
}
