#include <iostream>
using namespace std;

int stairCount;
int stairs[301] = {0};
int dp[301] = {0};

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> stairCount;
    for(int i = 1; i <= stairCount; i++) cin >> stairs[i];

    dp[1] = stairs[1];
    dp[2] = stairs[1] + stairs[2];
    for (int i = 3; i <= stairCount; i++)
    {
        dp[i] = max(dp[i - 3] + stairs[i] + stairs[i - 1], dp[i - 2] + stairs[i]);
    }
    cout << dp[stairCount];
}