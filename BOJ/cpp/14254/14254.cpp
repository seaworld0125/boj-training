#include <iostream>
#include <string>
using namespace std;

int main() {
    string str;
    cin >> str;

    int K;
    cin >> K;

    string oldPassword, newPassword;
    for(int i = 0; i < K; i++)
        oldPassword += str[i];
    
    int len = str.length();
    for(int i = len - K; i < len; i++)
        newPassword += str[i];

    int ans = 0;
    for(int i = 0; i < K; i++)
        if(oldPassword[i] != newPassword[i])
            ans++;
    
    cout << ans;
}