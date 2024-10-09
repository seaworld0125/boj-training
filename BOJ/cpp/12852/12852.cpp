#include <iostream>
using namespace std;

int N;
int dp[1000001];
int idx[1000001]; // 어디서 연산을 했는지

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> N;

    fill_n(dp, N + 1, (int)1e9);

    dp[1] = 0;
    dp[2] = 1;
    dp[3] = 1;
    
    idx[1] = 0;
    idx[2] = 1;
    idx[3] = 1;

    for(int i = 4; i <= N; i++) {

        if(i % 3 == 0) {
            int pdx = i / 3;
            if(dp[i] > dp[pdx] + 1) {
                dp[i] = dp[pdx] + 1;
                idx[i] = pdx;
            }
        }
        if(i % 2 == 0) {
            int pdx = i / 2;
            if(dp[i] > dp[pdx] + 1) {
                dp[i] = dp[pdx] + 1;
                idx[i] = pdx;
            }
        }
        if(dp[i] > dp[i - 1] + 1) {
            dp[i] = dp[i - 1] + 1;
            idx[i] = i - 1;        
        }
    }
    cout << dp[N] << endl;
    for(int i = N; i > 0;) {
        cout << i << ' ';
        i = idx[i];
    }
}