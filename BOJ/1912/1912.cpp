#include <iostream>
using namespace std;

int dp[100001];
int ans = -(int)1e9;

inline int max(int a, int b) {
    return (a > b ? a : b);
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n;
    cin >> n;

    for(int i = 1; i <= n; i++) {
        cin >> dp[i];
    }

    ans = dp[1];
    for(int i = 2; i <= n; i++) {
        dp[i] = max(dp[i], dp[i] + dp[i - 1]);
        ans = max(ans, dp[i]);        
    }

    cout << ans;
}