#ifndef TASK_3_MACHINE_H
#define TASK_3_MACHINE_H
#include <bits/stdc++.h>
#include <string>
using namespace std;
/*class Instructions{
public:
    void Load1(int operand1 , int operand2);
    void Load2();
    void Store1();
    void Store2();
    void Add1();
    void Add2();
    void jump();
    void Halt();
};*/

class Memory{
protected:
    map<int,int>Memo;
public:
    Memory();
    int read(int Address);
    void write(int Address,int Value);
};
class Register{
protected:
    int arr[16] = {0};
public:
    int get_register(int operand1);
    void write_register_address(int operand1,int operand2,Memory mem);
    void write_register(int operand1,int operand2);
};
class Machine{
protected:
    int programCounter;
    Register registers;
    Memory memory;
public:
    Machine():programCounter(0){}
    void executeStep(string& s);
    void fetchStep(string& s);
};


/*
class Instructions{
public:
    void Load1();
    void Load2();
    void Store1();
    void Store2();
    void Add1();
    void Add2();
    void jump();
    void Halt();
};

class Register{
private:
    int arr[16] = {0};

public:
    int read(int adress){
         arr[adress];
    }

    void write(int adress , int value){
         arr[adress] =value ;
    }
};

class Memory{
private:
    map<int , int >memo;
public:
    Memory(){
        for(int i=0 ; i<256 ; i++){
            memo[i]=0;
        }
    }
    int read(int adress){
        return memo[adress];
    }
    int write(int adress , int value){
       return memo[adress] =value ;
    }
};

class Machine{
protected:
    int programCounter;
    Register reg;
    Instructions inst;
    Memory mem;
public:
void excute(string inst);
void fetch(string filename);
};
*/

#endif //TASK_3_MACHINE_H
