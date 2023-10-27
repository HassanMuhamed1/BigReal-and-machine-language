//20230601 - ahd
//////////////1-string problem 
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

///////////////////////4-prime number
#include <bits/stdc++.h>

using namespace std;

int main ()
{
    int N;
    cout<<"enter the limit of your prime numbers: ";
    cin >> N;
    vector <int> v;
    for(int i=2; i<=N; i++)
    {
        bool prime = true;
        for(int j =2; j*j <= i; j++)
        {
            if(i % j == 0)
            {
                prime = false;
                break;
            }
        }
        if(prime)
        {
            v.push_back(i);
        }
    }
    int n = v.size();
    for(int i=0; i<n; i++)
    {
        cout<<"the prime numbers are"<<'\n';
        cout<<v[i]<<' ';
    }
}

/////////////////////7-The game of dominos
#include <bits/stdc++.h>

using namespace std;
struct dominoT
{
    int leftDots;
    int rightDots;
};

bool FormsDominoChain(vector<dominoT> & dominos)
{
    if(dominos.size())
        return true;

        for(int i=0; i<dominos.size(); i++)
        {
            if(dominos[i].leftDots == dominos[i-1].rightDots && i >0)
            {
                vector <dominoT> result = dominos;
                result.erase(result.begin() + i);
                if(FormsDominoChain(result))
                    return true;
            }
        }
        return false;
}

int main ()
{
    dominoT d1;
    vector <dominoT> dominos = {{2, 6},{6, 1},{1, 4},{4, 4},{4, 3}};
    if(FormsDominoChain)
    {
        for(int i=0; i<dominos.size(); i++)
            {
                cout<< dominos[i].leftDots<<'|'<<dominos[i].rightDots;
                if (i != dominos.size() - 1)
                    {
                        cout << " - ";
                    }
            }
    }
    else
        cout<<"you can't make a domino chain";
}

////////////////////10- Message Altering to Avoid Censorship
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

map <string , vector<string>> LoadLookupTable(const string &filename)
{
    map <string , vector<string>> lookupTable;
    ifstream file (filename);
    if(!file)
    {
        cout<<"cannot open the lookup table file";
        return lookupTable;
    }
    string line;
    while (getline (file,line))
    {
        string word;
        vector <string> alternatives;
        int pos = line.find(':');
        if(pos != string::npos)
        {
            word = line.substr(0 , pos);
            string alternativestring = line.substr(pos + 1);
            int start = 0;
            int end = alternativestring.find(',');
            while (end != string::npos)
            {
                string alternative = alternativestring.substr(start , end-start);
                alternatives.push_back(alternative);
                start = end + 1;
                end = alternativestring.find(',' , start);
            } 
            string lastAlternative = alternativestring.substr(start);
            alternatives.push_back(lastAlternative);
        }
        lookupTable[word] = alternatives;
    }
    file.close();
    return lookupTable;
}

string ReplaceWords (string &massege , map<string , vector<string>> &lookupTable)
{
    string replacedMessage = massege;
    random_device rd;
    mt19937 gen (rd());

    for(const auto& entry : lookupTable)
    {
        const string& word = entry.first;
        const vector <string>& alternatives = entry.second;
        uniform_int_distribution<> dis(0, alternatives.size() - 1);
        int pos = replacedMessage.find(word);
        while (pos != string::npos)
        {
            string replacement = alternatives[dis(gen)];
            replacedMessage.replace(pos , word.length(), replacement);
            pos = replacedMessage.find(word,pos + replacement.length());
        }
    }
    return replacedMessage;
}

int main ()
{
    string massegeFileName = "massage.txt";
    string lookUpTableFileName = "lookup_table.txt";
    ifstream massegeFile (massegeFileName);

    if(!massegeFile)
    {
        cout<<"the file cannot be open";
        return 1;
    }

    string massege ((istreambuf_iterator<char>(massegeFile)) , istreambuf_iterator<char>());
    massegeFile.close();

    map<string, vector<std::string>> lookupTable = LoadLookupTable(lookUpTableFileName);
    if (lookupTable.empty()) {
        return 1;
    }

    string replacedMassege = ReplaceWords(massege , lookupTable);
    cout<<"the original massege:"<<'\n';
    cout<<massege<<'\n';
    cout<<"the replaced massege:"<<'\n';
    cout<<replacedMassege<<'\n';
}