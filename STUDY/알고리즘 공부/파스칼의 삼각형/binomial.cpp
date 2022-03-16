#include <iostream>
using namespace std;

#define MAX 1001
int dp[MAX][MAX]; // 4,000,000 byte == 1mbyte

/*
        1
       1 1 
      1 2 1
     1 3 3 1
    1 4 6 4 1 
       ...

    if(col == 1) = 1
    if(col == row) = 1

    dp[3][2] = dp[2][1] + dp[2][2];

    dp[4][2] = dp[3][1] + dp[3][2];
    dp[4][3] = dp[3][2] + dp[3][3];

    ...

    dp[row][col] = dp[row - 1][col - 1] + dp[row - 1][col];
*/
void binomial(int N) {
    for(int row = 0; row <= N; row++) {
        for(int col = 0; col <= row; col++) {

            if(col == 0 || col == row) dp[row][col] = 1;

            else dp[row][col] = (dp[row - 1][col - 1] + dp[row - 1][col]) % 10007;
        }
    }
}

int main() {
    int N, K;
    cin >> N >> K;

    binomial(N);

    cout << dp[N][K];
}