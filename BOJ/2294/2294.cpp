#include <iostream>
#include <vector>
using namespace std;

#define INF (int)1e9

int dp[10001], coin[101];

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k;
    cin >> n >> k;

    fill_n(dp, k + 1, INF);
    dp[0] = 0;

    for(int i = 0; i < n; i++)
        cin >> coin[i];

    for(int i = 0; i < n; i++)
        for(int j = coin[i]; j <= k; j++)
            dp[j] = min(dp[j], 1 + dp[j - coin[i]]);

    cout << (dp[k] != INF ? dp[k] : -1);
}