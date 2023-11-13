#ifndef UNTITLED1_MACHINELANGUAGE_H
#define UNTITLED1_MACHINELANGUAGE_H


//class MachineLanguage {
//
//};
#include <bits/stdc++.h>
#include <string>
using namespace std;



class Memory{
protected:
    map<int,int>Memo;
public:
    Memory();
    int read(int Address);
    void write(int Address,int Value );
};
class Register{
protected:
    int arr[16] = {0};
public:
    int get_register(int operand1);
    void write_register_address(int operand1,int operand2,Memory mem);
    void write_register(int operand1,int operand2);
    void copy_register(string z);
    void Add1(int op1 , string op2 , bool carryFlag);

};


class MachineLanguage {
protected:
    int programCounter;
    Register registers;
    Memory memory;
public:
    MachineLanguage():programCounter(0){}
    void executeStep(string& s);
//    void fetchStep(string& s);
};


#endif //UNTITLED1_MACHINELANGUAGE_H
