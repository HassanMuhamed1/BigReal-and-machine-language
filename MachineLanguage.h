#ifndef UNTITLED1_MACHINELANGUAGE_H
#define UNTITLED1_MACHINELANGUAGE_H
#include <bits/stdc++.h>
#include <string>
using namespace std;
class Memory{
public:
    map<int,int>Memo;
    Memory();
    int read(int Address);
    void write(int Address,int Value );
};

class Register{
public:
    int arr[16] = {0};
    int get_register(int operand1);
    void write_register_address(int operand1,int operand2,Memory mem);
    void write_register(int operand1,int operand2);
    void copy_register(string z);
    void Add1(int op1 , string op2 );
};

class MachineLanguage {
protected:
    string fileName = "instructions.txt";

    string instruction;
public:
    int programCounter;
    Register registers;
    Memory memory;
    MachineLanguage():programCounter(0){}
    void readMemory(int programCounter ,Memory mem );
    void executeStep(string& s);
    void Jump(int op1 , int op2 , MachineLanguage & machine );
    bool isValid(string instruction);
};


#endif //UNTITLED1_MACHINELANGUAGE_H
