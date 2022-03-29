#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

string str1, str2, lcs = "";
int len1, len2, ans = 0;
int dp[1001][1001];

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> str1 >> str2;
    len1 = str1.length();
    len2 = str2.length();
    
    for(int i = 0; i <= len1; i++) {
        for(int j = 0; j <= len2; j++) {
            if(i == 0 || j == 0) {
                dp[i][j] = 0;
                continue;
            }       
            if(str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j -1]);
            }
            ans = max(ans, dp[i][j]);
        }
    }

    int i = len1;
    int j = len2;
    while(dp[i][j] != 0) {
        
        if(dp[i][j] == dp[i][j - 1])
            j--;
        else if(dp[i][j] == dp[i - 1][j])
            i--;
        else if(dp[i][j] == dp[i - 1][j - 1] + 1) {
            i--;
            j--;
            lcs = str1[i] + lcs;
        }
    }
    cout << ans << endl;
    cout << lcs;
}