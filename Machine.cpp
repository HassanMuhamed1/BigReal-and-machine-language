#include <bits/stdc++.h>
#include <string>
#include "Machine.h"
using namespace std;


/*void Machine ::fetchStep(string & filename){
    fstream instructionFile ("./" + filename);
    string line;
    while(getline(instructionFile , line)){
        executeStep(line);
    }
}*/
int Register::get_register(int operand1) {
    return arr[operand1] ;
}
void Register::write_register_address(int operand1, int operand2, Memory mem) {
    arr[operand1] = mem.read(operand2);
}
void Register::write_register(int operand1, int operand2) {
    arr[operand1] = operand2;
}

void Register::copy_register(int operand1) {
    arr[operand1 %10] = arr[(operand1/10)%10];
}

int Memory::read(int Address) {
    return Memo[Address];
}
void Memory::write(int Address, int Value) {
    Memo[Address] = Value;
}
Memory::Memory() {
    for (int i = 0; i < 256; ++i) {
        Memo[i] = {0};
    }
}
void Machine ::executeStep(string &inst){
    string x = inst.substr(0 , 3);
    string y = inst.substr(4 , 3);
    string z = inst.substr(8 , 4);

    int opCode = stoi(x, nullptr ,16 );
    int op1 = stoi(y, nullptr ,16 );
    int op2 = stoi(z, nullptr ,16 );

    registers.get_register(op1);
    registers.write_register(op1 , op2 );
    registers.write_register_address(op1 , op2, memory);

    switch (opCode){
        case 1:
            registers.write_register_address(op1 ,op2 , memory);
            break;
        case 2:
            registers.write_register(op1 , op2);
            break;
        case 3:
            if(op1 != 00){
                memory.write(op2 , registers.get_register(op1));
            }
            else{

            }
            break;
            // 4 0 A4
        case 4 :
            registers.copy_register(op1);
            break;
        case 5 :
            break;
        case 11:
            break;
        case 12 :
            break;
    }

}

