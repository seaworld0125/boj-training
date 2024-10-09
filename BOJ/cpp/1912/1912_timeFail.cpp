#include <iostream>
using namespace std;

int arr[100001];
int dp[100001];
int ans = -(int)1e9;

inline int max(int a, int b) {
    return (a > b ? a : b);
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n;
    cin >> n;

    for(int i = 1; i <= n; i++) {
        cin >> arr[i];
        dp[i] = arr[i];
        ans = max(arr[i], ans);
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 2; i + j - 1 <= n; j++) {
            dp[i] = dp[i] + arr[i + j - 1];
            ans = max(dp[i], ans);
        }
    }

    cout << ans;
}