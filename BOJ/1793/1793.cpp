#include <iostream>
#include <cstdio>
using namespace std;

unsigned long long dp[251];

int main() {
    int n;

    fill_n(dp, 251, -1);
    dp[0] = dp[1] = 1;

    while(scanf("%d", &n) != -1) {
        for(int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
    }
}