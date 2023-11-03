#include <bits/stdc++.h>
#include<cstring>
#include<string>
using namespace std;
class BigReal{
private:
    char sign = '+';
    string integer , fraction;
public:
    bool isValidReal(string real);
    BigReal(string real);
    string operator +(const BigReal & r1);
    bool operator ==(const BigReal & r1);
    bool operator <(const BigReal & r1);
    bool operator >(const BigReal &r1);
    BigReal operator <<(const BigReal & r1) const;
    void print();
    friend bool isValidReal(string real);
    friend ostream & operator << (ostream & output ,BigReal & r3){
        output <<r3.sign <<r3.integer<<'.'<<r3.fraction;
        return output;
    }
};
bool isValidReal(string real){
    bool valid=false;
    if(regex_match(real , regex("[+-]?\\d*.?\\d+"))){
        valid = true;
    }
    else{
        valid = false;
    }
    return valid;
}
BigReal ::BigReal(string real) {
    if(regex_match(real , regex("[+-]?\\d*.?\\d+"))){
        if(real[0] == '-'){
            sign = '-';
            real[0]='0';
        }
        else if(real[0] == '+'){
            sign = '+';
            real[0]='0';
        }
        integer = real.substr(0, real.find('.'));
        fraction = real.substr(real.find('.')+1, real.size()-1);
    }
    if(integer.size() == 0){
        integer = '0.0';
    }
    if(fraction.size() == 0){
        fraction = '0';
    }
}
string BigReal::operator+(const BigReal &r1) {
    int int1 = integer.size();
    int int2 = r1.integer.size();
    int frac1 = r1.fraction.size();
    int frac2 = fraction.size();

    int maxIntLen = max(int1, int2);
    int maxFracLen = max(frac1, frac2);

    string result2,result1;
    int carry = 0;

    // Handle the fractional part
    for (int i = maxFracLen - 1; i >= 0; --i) {
        int digit1 = (i < frac1) ? r1.fraction[i] - '0' : 0;
        int digit2 = (i < frac2) ? fraction[i] - '0' : 0;
        int sum = digit1 + digit2 + carry;

        if (sum < 10) {
            result2.insert(result2.begin(), sum + '0');
            carry = 0;
        } else {
            result2.insert(result2.begin(), (sum - 10) + '0');
            carry = 1;
        }
    }

    // Handle the integer part
    for (int i = maxIntLen - 1; i >= 0; --i) {
        int digit3 = (i < int1) ? r1.integer[i] - '0' : 0;
        int digit4 = (i < int2) ? integer[i] - '0' : 0;
        int sum1 = digit3 + digit4 + carry;

        if (sum1 < 10) {
            result1.insert(result1.begin(), sum1 + '0');
            carry = 0;
        } else {
            result1.insert(result1.begin(), (sum1 - 10) + '0');
            carry = 1;
        }
    }
    if (carry) {
        result1.insert(result1.begin(), '1');
    }
    // Determine the sign
    if (sign == '-' && r1.sign == '-') {
        result1.insert(result1.begin(), '-');
    }
    return ( result1+'.'+result2);
}
bool BigReal::operator==(const BigReal &r1) {
    if (sign == r1.sign) {
        if ((integer.size() == r1.integer.size()) && (fraction.size() == r1.fraction.size())) {
            for (int i = 0; i < integer.size(); i++) {
                if (integer[i] != r1.integer[i]) {
                    return false;
                }
            }
            for (int i = 0; i < fraction.size(); i++) {
                if (fraction[i] != r1.fraction[i]) {
                    return false;
                }
            }
        } else {
            return false; // Return false for the case where the integer and fraction parts have different sizes
        }
        return true; // Return true if all comparisons pass
    }
    return false; // Return false if the signs are not equal
}
bool BigReal::operator<(const BigReal &r1)
{
    // Check the signs
    if (sign != r1.sign)
    {
        // If signs are different, the one with the negative sign is smaller
        return (sign == '-');
    }
    else
    {
        // If signs are the same, compare the integer parts
        if (integer.length() != r1.integer.length())
        {
            // If lengths are different, the one with the longer integer part is larger
            return (integer.length() < r1.integer.length());
        }
        else
        {
            // If lengths are the same, compare lexicographically
            if (integer != r1.integer)
            {
                // If integer parts are different, compare them
                return (integer < r1.integer);
            }
            else
            {
                // If integer parts are the same, compare the fraction parts
                // Pad the shorter fraction with zeros to compare lexicographically
                string paddedFraction = fraction + string(max(0, (int)r1.fraction.length() - (int)fraction.length()), '0');
                string paddedR1Fraction = r1.fraction + string(max(0, (int)fraction.length() - (int)r1.fraction.length()), '0');

                return (paddedFraction < paddedR1Fraction);
            }
        }
    }
}
bool BigReal::operator>(const BigReal &r1)
{
    // Check the signs
    if (sign != r1.sign)
    {
        // If signs are different, the one with the positive sign is larger
        return (sign == '+');
    }
    else
    {
        // If signs are the same, compare the integer parts
        if (integer.length() != r1.integer.length())
        {
            // If lengths are different, the one with the longer integer part is larger
            return (integer.length() > r1.integer.length());
        }
        else
        {
            // If lengths are the same, compare lexicographically
            if (integer != r1.integer)
            {
                // If integer parts are different, compare them
                return (integer > r1.integer);
            }
            else
            {
                // If integer parts are the same, compare the fraction parts
                // Pad the shorter fraction with zeros to compare lexicographically
                string paddedFraction = fraction + string(max(0, (int)r1.fraction.length() - (int)fraction.length()), '0');
                string paddedR1Fraction = r1.fraction + string(max(0, (int)fraction.length() - (int)r1.fraction.length()), '0');

                return (paddedFraction > paddedR1Fraction);
            }
        }
    }
}
int main() {
    BigReal r1("-2220000000000000000000000000000000000000.77");
    BigReal r2("+222.7788888888888888888888888888888888888888888888888888888888888888888888");
    if(r1>r2){
        cout<<"R1 > R2";
    }
    else if(r1<r2){
        cout<<"R2 > R1";
    }
    else if(r1 == r2) cout<<"R1 = R2";
    return 0;
}
