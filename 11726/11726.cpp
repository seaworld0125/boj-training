#include <iostream>
#define ll long long
using namespace std;

ll dp[1001];
int n;

int main() {
    dp[1] = 1;
    dp[2] = 2;

    cin >> n;

    for(int i = 3; i <= n; i++) dp[i] = (dp[i - 1] + dp[i - 2]) % 10007;

    cout << dp[n];
}