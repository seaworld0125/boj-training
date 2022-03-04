#include <iostream>
#include <vector>
using namespace std;

int n, num;
int dp[501][501];

int getNum(int y, int x) {
    if(x < 0 || x > n) return -1;
    else return dp[y][x];
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    cin >> dp[1][0];

    for(int i = 2; i <= n; i++) {
        for(int j = 0; j < i; j++) {
            cin >> num;
            dp[i][j] = max(getNum(i - 1, j - 1), getNum(i - 1, j)) + num;    
        }
    }

    int ans = 0;
    for(int i = 0; i < n; i++)
        ans = max(ans, dp[n][i]);

    cout << ans;
}