
#include "MachineLanguage.h"
#include <bits/stdc++.h>
using namespace std;

void Register::Add1 (int op1 , string op2 ) {
    // Get the values from registers S and T
    int r1, r2;
    r1 = stoi(string(1, op2[2]), nullptr, 16);
    r2 = stoi(string(1, op2[3]), nullptr, 16);

    int valueS = arr[r1];
    int valueT = arr[r2];
    int carry = 0;
    int Sum = 0;
    bitset<8> bsS(valueS);
    bitset<8> bsT(valueT);
    bitset<8> bsSum;

    for (int i = 0; i < 8; ++i) {
        if(bsS[i]+bsT[i]+carry>1){
            if(bsS[i]+bsT[i]+carry==2){
                bsSum.reset(i);
            }
            else{
                bsSum.set(i);
            }
            carry = 1;
        }
        else{
            if(bsS[i]+bsT[i]+carry==1){
                bsSum.set(i);
            }
            else{
                bsSum.reset(i);
            }
            carry = 0;
        }
    }
    string res = bsSum.to_string();
    write_register(op1, (int)bitset<8> (res).to_ulong() );

}
int Register::get_register(int operand1) {
    return arr[operand1] ;
}
void Register::write_register_address(int operand1, int operand2, Memory mem) {
    arr[operand1] = mem.read(operand2);
}
void Register::write_register(int operand1, int operand2) {
    arr[operand1] = operand2;

}
void Register::copy_register(string z) {
    int r1 ,r2;
    r1 = stoi(string(1,z[2]) , nullptr ,16);
    r2 = stoi(string(1,z[3]) , nullptr ,16);
    arr[r1] = arr[r2];
}
int Memory::read(int Address) {
    return Memo[Address];
}
Memory::Memory() {
    for (int i = 0; i < 256; ++i) {
        Memo[i] = {0};
    }
}
void Memory::write(int Address, int Value) {
    Memo[Address] = Value;
}
void MachineLanguage::Jump(int op1, int op2, MachineLanguage &machine) {

    int position = programCounter;
    if(machine.registers.arr[op1] == machine.registers.arr[0]){
        programCounter = op2;
        for (int i = 0; i < position/2; ++i) {
            readMemory(programCounter , machine.memory);
        }
    }
}
void MachineLanguage::readMemory(int programCounter , Memory mem) {
    int opcode = mem.read(programCounter)/10;
    int op1 = mem.read(programCounter)%10;
    int op2  = mem.read(programCounter+1);

    stringstream operand1 , ope1 , ope2;
    operand1 << ::hex << opcode;
    ope1 << ::hex << op1;
    ope2 << ::hex << op2;
    string x = "0x"+operand1.str()+" ";
    string y = "0x"+ope1.str()+" ";
    string z = "0x"+ope2.str();
    string instruction = x+y+z;
    executeStep(instruction);
}
void MachineLanguage ::executeStep(string &inst ){
    string IR;
    string x = inst.substr(0 , 3);
    string y = inst.substr(4 , 3);
    string z = inst.substr(8 , 4);
// 10a3
    int opCode = stoi(x, nullptr ,16 );
    int op1 = stoi(y, nullptr ,16 );
    int op2 = stoi(z, nullptr ,16 );

    memory.write(programCounter++ , opCode*10+op1);
    memory.write(programCounter++ , op2);

    switch (opCode){
        case 1:
            IR +=("Load address of "+ z.substr(2 ,2) +" to register "+y.substr(2,1) );
            registers.write_register_address(op1 ,op2 , memory);
            break;
        case 2:
            IR +=(",Load to register "+ y.substr(2,1) +" value: "+z.substr(2 ,2) );
            registers.write_register(op1 , op2);
            break;
        case 3:
            if(op1 != 00){
                IR +=(",the contents of register "+ y.substr(2,1) +" placed in memory cell  "+z.substr(2 ,2) );
                memory.write(op2 , registers.get_register(op1));
            }
            else{
                IR += (",Writing to 00 is writing to screen");
                cout<<"register number "<<z[2]<<registers.get_register(op1);
            }
            break;
        case 4 :
            IR += (",the contents of register" +to_string(z[0])+ "to be copied into register" + to_string(z[1]));
            registers.copy_register(z);
            break;
        case 5 :
            IR += (",values in registers "+ to_string(z[0])+" and "+ to_string(z[1])+ " to be added and the sum placed in register " +y.substr(2,1));
            registers.Add1(op1 , z );
            break;
        case 11:
            IR += (",Jump to instruction in address "+z.substr(2 ,2)+" if the register "+y.substr(2,1)+" equal to register 0");
            this->Jump(op1 ,op2 , *this );
            break;
        case 12 :
            IR += ("Halt");

            break;
        default:
            cout<<"wrong operation \n";
            break;
    }
    cout<<'\n'<<"IR: "<<IR<<endl;
}
bool MachineLanguage::isValid(std::string instruction) {
    bool right[3]{false,false,false};
    if(isxdigit(static_cast<unsigned char>(instruction[2]))){
        right[0] = true;
    }
    if (isxdigit(static_cast<unsigned char>(instruction[6]))){
        right[1] = true;
    }
    if(isxdigit(static_cast<unsigned char>(instruction[10]))&&isxdigit(static_cast<unsigned char>(instruction[11]))){
        right[2] = true;
    }
    if(instruction[2]=='4'&&instruction[6]!='0'&&isxdigit(static_cast<unsigned char>(instruction[10]))&&
       isxdigit(static_cast<unsigned char>(instruction[11]))){
        return false;
    }
    if(instruction[2]=='C'&&instruction[6]!='0'&&instruction[10]!='0'&&instruction[11]!='0'){
        return false;
    }
    if(right[0]&&right[1]&&right[2]){
        return true;
    }
    else{
        return false;
    }
}
