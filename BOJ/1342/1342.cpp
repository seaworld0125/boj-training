#include <iostream>
#include <string>
using namespace std;

int arr[26] = {0};
int ans = 0;

void recursive(int len, int idx, int c) {
    if(len == idx) ans++;

    for(int i = 0; i < 26; i++) {
        if(!arr[i] || c == i) continue;

        arr[i]--;
        recursive(len, idx + 1, i);
        arr[i]++;
    }
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    string str;
    cin >> str;

    for(char c : str) arr[c - 'a']++;

    for(int i = 0; i < 26; i++) {
        if(!arr[i]) continue;

        arr[i]--;
        recursive(str.length() - 1, 0, i);
        arr[i]++;
    }
    cout << ans;
}   