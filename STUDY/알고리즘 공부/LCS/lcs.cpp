#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string str1, str2;

    cin >> str1 >> str2;

    int dp[50][50];
    fill_n(dp[0], 2500, 0);

    int len1 = str1.length(), len2 = str2.length();
    int lcsLength = 0;

    cout << "Get lcs length\n";
    for(int i = 1; i <= len2; i++) {
        for(int j = 1; j <= len1; j++) {
            if(str1[j - 1] == str2[i - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
            lcsLength = max(lcsLength, dp[i][j]);
        }
    }
    cout << "length :" << lcsLength << endl;

    cout << "\nGet lcs\n";
    string lcs = "";
    for(int i = len2; i > 0; i--) {
        for(int j = len1; j > 0; j--) {
            if(dp[i][j] == dp[i - 1][j - 1] + 1 
                && dp[i][j] == dp[i - 1][j] + 1 
                && dp[i][j] == dp[i][j - 1] + 1) {
                
                lcs = str2[i - 1] + lcs;
                break;
            }
        }
    }
    cout << "lcs :" << lcs << endl;
}