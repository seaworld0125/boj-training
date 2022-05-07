#include <iostream>
using namespace std;

int N;
long long dp[91];

void recursive(int n) {
    dp[n] = dp[n - 1] + dp[n - 2];

    if(n == N) return;
    else recursive(n + 1);
}

int main() {
    cin >> N;

    dp[1] = 1;
    dp[2] = 1;
    if(N > 2) recursive(3);
    
    cout << dp[N];
}