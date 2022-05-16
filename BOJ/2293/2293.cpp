#include <iostream>
using namespace std;

int n, k;
int coins[1001]; // 동전
int dp[10001]; // 가치

int main() {

    cin >> n >> k;

    for(int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    dp[0] = 1;

    for(int i = 0; i < n; i++) { // 동전 리스트 순회
        int coin = coins[i];

        for(int j = coin; j <= k; j++) { // 현재 동전으로 만들 수 있는 가치
            dp[j] += dp[j - coin];
        }
    }

    cout << dp[k];
}