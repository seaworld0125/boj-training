#include <cmath>
#include <queue>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

#define ALPHABET 26

bool check(vector<int> original, string& word) {
    queue<char> st;
    for(auto& c : word) {
        st.emplace(c);
    }

    int size = st.size();
    while(size--) {
        auto c = st.front();
        int idx = c - 'A';

        if(original[idx]) {
            original[idx]--;
        }
        else {
            st.emplace(c);
        }
        st.pop();
    }

    if(st.size() > 1) return false;

    int acc = 0;
    for(int i = 0; i < ALPHABET; i++) {
        acc += original[i];
        if(acc > 1) return false;
    }

    return true;
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);

    int res = 0;
    int originalLen;
    vector<int> original(ALPHABET, 0);

    int n;
    cin >> n;
    n--;

    string word;
    cin >> word;

    originalLen = word.length();
    for(auto& c : word)
        original[c - 'A']++;

    int sub;
    while(n--) {
        cin >> word;
        sub = abs(originalLen - (int)word.length());

        if(sub > 1) continue;

        if(check(original, word)) res++;
    }
    cout << res;
}