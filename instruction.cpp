#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "instruction.h"

const char* extractInstr(std::string s){
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

    return format[s].c_str();
}

std::string convertReg(char c){
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

std::string littleToBigEndian(std::string s){
    std::string t = "";
    
    for(int i = s.length() / 2; i >= 0; i--){
        t += s.substr(i*2, 2);
    }
    
    return "0x" + t;
}

void instruction(std::string s){
    std::string instr = s.substr(0, 2);

    if(s.length() == 16)
        printf("%s %s", ".quad", littleToBigEndian(s).c_str());
    
    else if(s[0] == '0' || s[0] == '1' || s[0] == '9')
        printf("%s", extractInstr(instr));
    
    else if(s[0] == '2' || s[0] == '6')
        printf("%s %s, %s", extractInstr(instr), convertReg(s[2]).c_str(), convertReg(s[3]).c_str());
   
    else if(s[0] == '3')
        printf("%s $%s, %s", extractInstr(instr), offset(s.substr(4, s.length())).c_str(), convertReg(s[3]).c_str());
    
    else if(s[0] == '4')
        printf("%s %s, $%s (%s)", extractInstr(instr), convertReg(s[2]).c_str(), offset(s.substr(4, s.length())).c_str(), convertReg(s[3]).c_str()); 
    
    else if(s[0] == '5')
        printf("%s $%s (%s), %s", extractInstr(instr), offset(s.substr(4, s.length())).c_str(), convertReg(s[3]).c_str(), convertReg(s[2]).c_str()); 
   
    else if(s[0] == '7' || s[0] == '8')
        printf("%s %s", extractInstr(instr), offset(s.substr(2, s.length())).c_str());
   
    else if(!instr.compare("a0") || !instr.compare("A0") || !instr.compare("b0") || !instr.compare("B0"))
        printf("%s %s", extractInstr(instr), convertReg(s[2]).c_str());
    
    else
        printf("%s", "illegal op");
        //printf("%s", extractInstr(instr));

}

std::string offset(std::string s){
    std::string t = "";
    
    for(int i = s.length() / 2; i >= 0; i--){
        t += s.substr(i*2, 2);
    }
    
    t = t.erase(0, t.find_first_not_of('0'));
   
    if(t == "")
        return "0x0";

    else
        return "0x" + t;
}
