#include <iostream>
using namespace std;

#define INF (int)1e9
#define F first
#define S second

int N, T, P;
pair<int, int> schedule[16];
int dp[16] = {0};

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> N;

    for(int i = 1; i <= N; i++) {
        cin >> T >> P;

        schedule[i] = {T, P};
    }

    int ans = 0;

    for(int i = N; i > 0; i--) {
        
        int endDay = i + schedule[i].F - 1;
        if(endDay > N) continue;

        int cost = schedule[i].S; // 비용 계산
        int maxCost = 0;

        for(int j = i + schedule[i].F; j <= N; j++) { // 선택할 수 있는 값 중에 가장 큰 dp 값 선택
            maxCost = max(maxCost, dp[j]);
        }

        if(dp[i] < cost + maxCost) { // dp 갱신
            dp[i] = cost + maxCost; 
            ans = max(ans, dp[i]);
        }
    }
    cout << ans;
}