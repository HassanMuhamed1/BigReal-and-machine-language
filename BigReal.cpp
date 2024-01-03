#include "Bigreal.h"
#include <bits/stdc++.h>
using namespace std;
bool isValidReal(const string& real){
    bool valid=false;
    if(regex_match(real , regex("[+-]?\\d*.?\\d+"))){
        valid = true;
    }
    else{
        valid = false;
    }
    return valid;
}
//------------------------------------------------------------------------------------------------
BigReal ::BigReal(string real) {
    if(regex_match(real , regex("[+-]?\\d*.?\\d+"))){
        if(real[0] == '-'){
            sign = '-';
        }
        else if(real[0] == '+'){
            sign = '+';
        }
        if(real[0]=='+'||real[0]=='-'){
            integer = real.substr(1, real.find('.')-1);
        }
        else{
            // if sign there no exist here
            integer = real.substr(0, real.find('.'));
        }
        fraction = real.substr(real.find('.')+1, real.size()-1);
    }
    if(real.find('.')>real.size()){// real.find will return any number if will find no point
        fraction='0';
    }
    if(integer.empty()){
        integer = '0';
    }
    if(fraction.empty()){
        fraction = '0';
    }
}
//------------------------------------------------------------------------------------------------
string BigReal::operator+(BigReal r1) {
    int int1 = (int)integer.size();
    int int2 = (int)r1.integer.size();
    int frac1 = (int)fraction.size();
    int frac2 = (int)r1.fraction.size();

    int maxIntLen = max(int1, int2);
    int maxFracLen = max(frac1, frac2);
    string result2,result1;
    int carry = 0;
    // Handle the fractional part
    if(int1 >int2){
        int dif = int1 - int2;
        string pad;
        for (int i = 0; i < dif; ++i) {
            pad+='0';
        }
        r1.integer = pad + r1.integer;
    }
    else if(int2>int1){
        int dif = int2 - int1 ;
        string pad;
        for (int i = 0; i < dif; ++i) {
            pad+='0';
        }
        integer = pad + integer;
    }
    if(frac1 >frac2){
        int dif = frac1 - frac2;
        string pad;
        for (int i = 0; i < dif; ++i) {
            pad+='0';
        }
        r1.fraction =  r1.fraction + pad;
    }
    else if(frac2>frac1){
        int dif = frac2 - frac1 ;
        string pad;
        for (int i = 0; i < dif; ++i) {
            pad+='0';
        }
        fraction =  fraction+pad;
    }
    if(sign == r1.sign){
        for (int i = maxFracLen - 1; i >= 0; --i) {
            int digit1 = fraction[i] - '0' ;
            int digit2 = r1.fraction[i] - '0';
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
            int digit3 = integer[i] - '0' ;
            int digit4 = r1.integer[i]-'0' ;
            int sum1 = digit3 + digit4 + carry;

            if (sum1 < 10) {
                result1.insert(result1.begin(), sum1 + '0');  // Insert at the beginning
                carry = 0;
            } else {
                carry = 1;
                result1.insert(result1.begin(), (sum1 - 10) + '0');  // Insert at the beginning

            }
        }

        if (carry) {
            result1.insert(result1.begin(), '1');  // Insert at the beginning
        }

        // Determine the sign
        if(integer>r1.integer){
            return (sign+result1+'.'+result2);
        }
        else if(integer<r1.integer){
            return (r1.sign+result1+'.'+result2);
        }
        else{
            if(fraction>r1.fraction){
                return (sign+result1+'.'+result2);
            }
            else{
                return (r1.sign+result1+'.'+result2);
            }
        }
    }
    else if(sign == '-' && r1.sign =='+'){
        if(integer >= r1.integer){
            int borrow = 0;

            // Handle the fractional part
            for (int i = maxFracLen - 1; i >= 0; --i) {
                int digit1 = fraction[i] - '0' ;
                int digit2 =  r1.fraction[i] - '0' ;
                int sub = digit1 - digit2 - borrow;
                if (sub < 0) {
                    sub += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                if(i==0 && sub<0){
                    borrow=1;
                }
                char x= sub +'0';
                result2.push_back(x);

            }
            reverse(result2.begin(), result2.end());

            // Handle the integer part
            for (int i = maxIntLen - 1; i >= 0; --i) {
                int digit3 = integer[i] - '0';
                int digit4 = r1.integer[i] - '0' ;
                int sub = digit3 - digit4 - borrow;
                if (sub < 0) {
                    sub += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                char y= sub+'0';
                result1.push_back(y);
            }
            reverse(result1.begin(), result1.end());
            sign = '-';
            return (sign+result1+'.'+result2);
        }
        else if(integer <= r1.integer){
            int borrow = 0;

            // Handle the fractional part
            for (int i = maxFracLen - 1; i >= 0; --i) {
                int digit1 = r1.fraction[i] - '0' ;
                int digit2 = fraction[i] - '0' ;
                int sub = digit1 - digit2 - borrow;
                if (sub < 0) {
                    sub += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                if(i==0 && sub<0){
                    borrow=1;
                }
                char x= sub +'0';
                result2.push_back(x);

            }
            reverse(result2.begin(), result2.end());

            // Handle the integer part
            for (int i = maxIntLen - 1; i >= 0; --i) {
                int digit3 = r1.integer[i] - '0' ;
                int digit4 = integer[i] - '0' ;
                int sub = digit3 - digit4 - borrow;
                if (sub < 0) {
                    sub += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                char y= sub+'0';
                result1.push_back(y);
            }
            sign = '+';
            reverse(result1.begin(), result1.end());
            /*if(integer>r1.integer){
                return (sign+result1+'.'+result2);
            }
            else if(integer<r1.integer){
                return (r1.sign+result1+'.'+result2);
            }
            else{
                if(fraction>r1.fraction){
                    return (sign+result1+'.'+result2);
                }
                else{
                    return (r1.sign+result1+'.'+result2);
                }
            }*/
            return (sign+result1+'.'+result2);
        }
    }
    r1.sign = '+';
    return this->operator-(r1);
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
//------------------------------------------------------------------------------------------------
bool BigReal::operator<(const BigReal &r1)
{
    // Check the signs
    if (sign != r1.sign)
    {
        // If signs are different, the one with the negative sign is smaller
        return false;
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
//------------------------------------------------------------------------------------------------
bool BigReal::operator>(const BigReal &r1)
{
    // Check the signs
    if (sign != r1.sign)
    {
        // If signs are different, the one with the positive sign is larger
        return false;
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
string BigReal::operator- (BigReal r1) {
    char signs;
    if(*this >r1){
        signs = this->sign;
    }
    else{
        if(r1.sign=='-'){ signs = '+'; }
        else{
            signs = '-';
        }
    }
    int int1 = (int)integer.size();
    int int2 = (int)r1.integer.size();
    int frac1 = (int)fraction.size();
    int frac2 = (int)r1.fraction.size();
    string result2,result1;
    int carry = 0;

    int maxIntLen = max(int1, int2);
    int maxFracLen = max(frac1, frac2);
    if(int1 >int2){
        int dif = int1 - int2;
        string pad;
        for (int i = 0; i < dif; ++i) {
            pad+='0';
        }
        r1.integer = pad + r1.integer;
    }
    else if(int2>int1){
        int dif = int2 - int1 ;
        string pad;
        for (int i = 0; i < dif; ++i) {
            pad+='0';
        }
        integer = pad + integer;
    }
    if(frac1 >frac2){
        int dif = frac1 - frac2;
        string pad;
        for (int i = 0; i < dif; ++i) {
            pad+='0';
        }
        r1.fraction =  r1.fraction + pad;
    }
    else if(frac2>frac1){
        int dif = frac2 - frac1 ;
        string pad;
        for (int i = 0; i < dif; ++i) {
            pad+='0';
        }
        fraction =  fraction+pad;
    }
    if(sign == r1.sign){
        if(integer>=r1.integer ){
            int borrow = 0;
            // Handle the fractional part
            for (int i = maxFracLen - 1; i >= 0; --i) {
                int digit1 = fraction[i] - '0' ;
                int digit2 = r1.fraction[i] - '0' ;
                int sub = digit1 - digit2 - borrow;
                if (sub < 0) {
                    sub += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                if(i==0 && sub<0){
                    borrow=1;
                }
                char x= sub +'0';
                result2.push_back(x);

            }
            reverse(result2.begin(), result2.end());

            // Handle the integer part
            for (int i = maxIntLen - 1; i >= 0; --i) {
                int digit3 = integer[i] - '0' ;
                int digit4 = r1.integer[i] - '0' ;
                int sub = digit3 - digit4 - borrow;
                if (sub < 0) {
                    sub += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                char y= sub+'0';
                result1.push_back(y);
            }
            reverse(result1.begin(), result1.end());
            return (sign+result1+'.'+result2);
        }
        else if(integer<=r1.integer ){
            int borrow = 0;
            // Handle the fractional part
            for (int i = maxFracLen - 1; i >= 0; --i) {
                int digit1 = r1.fraction[i] - '0' ;
                int digit2 = fraction[i] - '0' ;
                int sub = digit1 - digit2 - borrow;
                if (sub < 0) {
                    sub += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                if(i==0 && sub<0){
                    borrow=1;
                }
                char x= sub +'0';
                result2.push_back(x);

            }
            reverse(result2.begin(), result2.end());

            // Handle the integer part
            for (int i = maxIntLen - 1; i >= 0; --i) {
                int digit3 = r1.integer[i] - '0' ;
                int digit4 = integer[i] - '0' ;
                int sub = digit3 - digit4 - borrow;
                if (sub < 0) {
                    sub += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                char y= sub +'0';
                result1.push_back(y);
            }
            reverse(result1.begin(), result1.end());
            return (signs+result1+'.'+result2);
        }
        /*else{
            if(fraction>r1.fraction){
                return (sign+result1+'.'+result2);
            }
            else{
                return (r1.sign+result1+'.'+result2);
            }
        }*/
    }
    else if(sign == '-' && r1.sign == '+'){
        if(integer<r1.integer || integer > r1.integer){
            for (int i = maxFracLen - 1; i >= 0; --i) {
                int digit1 = fraction[i] - '0' ;
                int digit2 = r1.fraction[i] - '0' ;
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
                int digit3 = integer[i] - '0' ;
                int digit4 =  r1.integer[i] - '0' ;
                int sum1 = digit3 + digit4 + carry;

                if (sum1 < 10) {
                    result1.insert(result1.begin(), sum1 + '0');  // Insert at the beginning
                    carry = 0;
                } else {
                    result1.insert(result1.begin(), (sum1 - 10) + '0');  // Insert at the beginning
                    carry = 1;
                }
            }

            if (carry) {
                result1.insert(result1.begin(), '1');  // Insert at the beginning
            }
            bool greater = true;
            if(integer>r1.integer){
                return (signs+result1+'.'+result2);
            }
            else if(integer<r1.integer){
                return (signs+result1+'.'+result2);
            }
            else{
                if(fraction>r1.fraction){
                    return (signs+result1+'.'+result2);
                }
                else if(fraction > r1.fraction){
                    return (signs+result1+'.'+result2);
                }
                else{
                    return (signs+result1+'.'+result2);
                }
            }
        }
    }
    r1.sign = '+';
    return this->operator+(r1);
} // signs is have a problem
