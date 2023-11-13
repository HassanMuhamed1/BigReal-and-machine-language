#include "MachineLanguage.h"
using namespace std;

void Register::Add1 (int op1 , string op2 , bool carryFlag) {
    // Get the values from registers S and T
    int r1 ,r2;
    r1 = stoi(string(1,op2[2]) , nullptr ,16);
    r2 = stoi(string(1,op2[3]) , nullptr ,16);

    int valueS = arr[r1];
    int valueT = arr[r2];

    // Convert the values to bitsets with 8 bits
    bitset<8> bsS(valueS);
    bitset<8> bsT(valueT);

    // Perform the binary addition
    bitset<9> bsSum = bsS.to_ulong() + bsT.to_ulong();

    // Check for carry
    if (bsSum[8] == 1) {
        bsSum[8] = 0;  // Clear the carry bit
        carryFlag = true;
    } else {
        carryFlag = false;
    }

    // Store the result in register R
    write_register(op1, bsSum.to_ulong());
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

void MachineLanguage ::executeStep(string &inst){
    string x = inst.substr(0 , 3);
    string y = inst.substr(4 , 3);
    string z = inst.substr(8 , 4);

    int opCode = stoi(x, nullptr ,16 );
    int op1 = stoi(y, nullptr ,16 );
    int op2 = stoi(z, nullptr ,16 );

    memory.write(programCounter++ , opCode*10+op1);
    memory.write(programCounter++ , op2);

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
                cout<<"register number "<<z[2]<<registers.get_register(op1);
            }
            break;
            // 4 0 A4
        case 4 :
            registers.copy_register(z);
            break;
        case 5 :
            bool CaryFlag = false;
            registers.Add1(op1 , z ,CaryFlag );
            break;
//        case 11:
//            break;
//        case 12 :
//            break;
//        default:
//            cout<<"wrong operation \n";
    }

}
