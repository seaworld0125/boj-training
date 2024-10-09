#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#define F first
#define S second
#define pii pair<int, int>
#define MAXC 10001
#define INF (int)1e9

int dp[101][MAXC];

int main() {
    int N, M;
    cin >> N >> M;

    vector<pii> apps(N + 1);
    
    for(int i = 1; i <= N; i++) cin >> apps[i].F;
    for(int i = 1; i <= N; i++) cin >> apps[i].S;

    // fill_n(dp, MAXC, 0);
    memset(dp[0], 0, sizeof(dp));

    int n_mem, 
        n_cost,
        ans = INF;

    for(int i = 1; i <= N; i++) {
        n_mem = apps[i].F,
        n_cost = apps[i].S;

        for(int j = 0; j < 10001; j++) { 
            if(n_cost <= j)
                dp[i][j] = max(dp[i - 1][j], n_mem + dp[i - 1][j - n_cost]);           
            else
                dp[i][j] = dp[i - 1][j];

            if(dp[i][j] >= M) {
                ans = min(ans, j);
            }
        }
    }
    cout << ans;
}