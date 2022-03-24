#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int dp[101][101][101];

int main() {
    string str1, str2, str3;
    cin >> str1 >> str2 >> str3;

    int len1 = str1.length(), 
        len2 = str2.length(), 
        len3 = str3.length(),
        ans = 0;

    for(int i = 0; i <= len1; i++) {
        for(int j = 0; j <= len2; j++) {
            for(int k = 0; k <= len3; k++) {
                if(i == 0 || j == 0 || k == 0) {
                    dp[i][j][k] = 0;
                    continue;
                }
                if(str1[i - 1] == str2[j - 1] && str2[j - 1] == str3[k - 1]) {
                    dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
                }
                else {
                    dp[i][j][k] = max(dp[i - 1][j][k], max(dp[i][j - 1][k], dp[i][j][k - 1]));
                }
                ans = max(dp[i][j][k], ans);
            }
        }
    }
    cout << ans;
}