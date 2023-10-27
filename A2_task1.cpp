#include <bits/stdc++.h>

using namespace std;

int main()
{
    string s,s2;
    cout<<"Enter the string you want to correct: "; 
    char prevchar=' ';
    bool firstchar = true;
    getline(cin, s);

    for(char c : s)
    {
        if(isspace(c))
        {
            if(!isspace(prevchar) && !firstchar)
                s2 += ' ';
        }
        else
        {
            if(firstchar)
            {
                s2 += toupper(c);
                firstchar = false;
            }
            else
            {
                s2 += tolower(c);
            }
        }
        prevchar = c;
    }
    cout << s2 << '\n';

    return 0;
}