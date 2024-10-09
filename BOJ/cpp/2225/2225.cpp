#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int N, K;
    cin >> N >> K;

    int dp[201][201] = {0};

    for(int i = 0; i <= N; i++) {
        dp[1][i] = 1;
        dp[2][i] =  i + 1;
    }

    for(int i = 3; i <= K; i++) {
        for(int j = 0; j <= N; j++) {
            for(int h = 0; h <= j; h++) {
                dp[i][j] = (dp[i][j] + dp[i - 1][h]) % (int)1e9;
            }
        }
    }

    cout << dp[K][N];
}