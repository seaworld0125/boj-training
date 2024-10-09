#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

#define endl '\n'

vector<char> vowel;
vector<char> cons;
vector<char> charList;
vector<string> keyList;

int L, C; 
int maxVowelCount;
int maxConsCount;

inline bool isVowel(char& c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

void selectCons(int count, int now) {
    if(count == maxConsCount) {
        // cout << "[select comp]! ";
        string key(charList.begin(), charList.end());
        sort(key.begin(), key.end());
        // cout << key << endl;
        keyList.emplace_back(key);
        return;
    }

    for(int i = now; i < cons.size(); i++) {
        charList.emplace_back(cons[i]);
        selectCons(count + 1, i + 1);
        charList.pop_back();
    }
}

void selectVowel(int count, int now) {
    if(count == maxVowelCount) {
        // cout << "[vowel]\n";
        // for(int i = 0; i < charList.size(); i++) {
        //     cout << charList[i] << " ";
        // }cout << endl;
        selectCons(0, 0);
        return;
    }

    for(int i = now; i < vowel.size(); i++) {
        charList.emplace_back(vowel[i]);
        selectVowel(count + 1, i + 1);
        charList.pop_back();
    }
}

int main() {
    cin >> L >> C; 

    char c;
    while(C--) {
        cin >> c;
        
        if(isVowel(c)) 
            vowel.emplace_back(c);
        else 
            cons.emplace_back(c);
    }

    for(int i = 1; i <= L - 2 && i <= 5; i++) {
        maxVowelCount = i;
        maxConsCount = L - i;
        selectVowel(0, 0);
    }

    sort(keyList.begin(), keyList.end());
    for(string key : keyList) {
        cout << key << endl;
    }
}