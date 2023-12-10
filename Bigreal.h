#ifndef BIGREAL_BIGREAL_H
#define BIGREAL_BIGREAL_H
#include <bits/stdc++.h>
#include <string>
using namespace std;
class BigReal{
private:
    char sign = '+';
    string integer="0" , fraction="0";
public:
    bool isValidReal(string real);
    BigReal(string real);
    string operator +(BigReal  r1);
    string operator -(BigReal r1);
    bool operator ==(const BigReal & r1);
    bool operator <(const BigReal & r1);
    bool operator >(const BigReal &r1);
    BigReal operator <<(const BigReal & r1) const;
    void print();
    friend bool isValidReal(const string& real);
    friend ostream & operator << (ostream & output ,BigReal & r3){
        output << r3.sign <<r3.integer <<'.'<<r3.fraction;
        return output;
    }
};
#endif //BIGREAL_BIGREAL_H
