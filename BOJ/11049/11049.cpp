#include <iostream>
#include <algorithm>
using namespace std;

#define ll long long

int N, 
    r, 
    c,
    row[501], 
    col[501];

ll dp[501][501];

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;

    for(int i = 0; i < N; i++) {
        cin >> row[i];
        cin >> col[i];
    }

    for(int len = 1; len < N; len++) {
        for(int i = 0; i + len < N; i++) {

            int j = i + len;
            ll Min = (ll)1e9;

            for(int k = i; k < j; k++) {
                Min = min(Min, dp[i][k] + dp[k + 1][j] + (row[i] * col[k] * col[j]));
            }
            dp[i][j] = Min;
        }
    }
    cout << dp[0][N - 1];
}