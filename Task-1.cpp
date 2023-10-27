// Problem-3 =>Hassan
#include <bits/stdc++.h>
#include <string>
#define Hassan ios_base::sync_with_stdio(false); cin.tie(nullptr);
using namespace std;

vector<string> split(string target, string delimiter){
    vector<string>res;
    string s;
    for (int i = 0; i < target.size(); ++i) {
        if(target[i]==',' || target[i]==' ')res.push_back(delimiter);
        else if(i==0 || i==target.size()){
            s+='"';
            res.push_back(s);
            s.clear();
        }
        else{
            s+=target[i];
            res.push_back(s);
            s.clear();
        }
    }
    for (vector<string>::iterator it=res.begin() ; it!=res.end() ; it++) {
        cout<<*it;
    }
}
int main() {
    Hassan;
    string target , delimiter;
    getline(cin ,target);
    getline(cin ,delimiter);
    vector<string>out = split(target, delimiter);
    return 0;
}
========================================================================
========================================================================
// problem-9 => Hassan
#include <bits/stdc++.h>
using namespace std;
bool bears(int n) {
    if (n == 42) {
        return true;
    }
    if (n < 42) {
        return false;
    }
    if (n % 2 == 0 && bears(n / 2)) {
        return true;
    }
    if ((n % 10) * ((n % 100) / 10) != 0 && bears(n - ((n % 10) * ((n % 100) / 10)))) {
        return true;
    }
    if (n % 5 == 0 && bears(n - 42)) {
        return true;
    }
    return false;
}
int main() {
    int n;
    cout << "Enter the number of bears: ";
    cin >> n;
    if (bears(n)){
        cout<<"You have reached the goal!"<<endl;
    }
    else{
        cout<<"You haven't reached the goal!"<<endl;
    }
    return 0;
}
===============================================================
===============================================================
// problem-6-a => Hassan
#include <bits/stdc++.h>
using namespace std;
void binaryPrint(int n){
    if(n>1){
        binaryPrint(n/2);
    }
    cout<<n%2;
}
int main() {
    int n;
    cout<<"Enter decimal num: ";
    cin>>n;
    cout<<"Binary: ";
    binaryPrint(n);

    return 0;
}
=================================================================
=================================================================
// problem-6-b => Hassan
#include <bits/stdc++.h>
using namespace std;
 void numbers(string prefix, int k){
     if(k!=0){
         numbers(prefix+'0' , k-1);
         numbers(prefix+'1' , k-1);
     }
     else{
         cout<<prefix<<endl;
     }
}
int main() {
     string prefix;
     int k;
    cin>>prefix>>k;
    numbers(prefix,k);

    return 0;
}

