#include <iostream>
#define INF (int)1e9
using namespace std;

enum { RED, GREEN, BLUE };

int N;
int cost[1001][3], dp[1001][3];

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;

    for(int i = 1; i <= N; i++) {
        for(int j = 0; j < 3; j++) {
            cin >> cost[i][j];
            dp[i][j] = cost[i][j];
        }
    }
    
    for(int i = 2; i <= N; i++) {
        dp[i][RED] = min(dp[i - 1][GREEN], dp[i - 1][BLUE]) + dp[i][RED];
        dp[i][GREEN] = min(dp[i - 1][RED], dp[i - 1][BLUE]) + dp[i][GREEN];
        dp[i][BLUE] = min(dp[i - 1][GREEN], dp[i - 1][RED]) + dp[i][BLUE];
    }

    cout << min(dp[N][RED], min(dp[N][GREEN], dp[N][BLUE]));
}