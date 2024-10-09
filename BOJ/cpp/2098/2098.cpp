#include <iostream>
#include <algorithm>
using namespace std;

#define INF (int)1e9

int N;                  // N
int dist[16][16];       // 정점 간의 거리
int dp[16][1 << 16];    // DP
int finalStatus;        // 마지막 최종 상태 (1 << N) - 1

int dfs(int now, int status) {                              // 현재 정점 번호와 방문 상태를 받는다
    if(status == finalStatus) return dist[now][0];          // 만약 최종 상태 값과 현재 상태 값이 같다면 모든 정점을 방문한 것이다. 
                                                            // 0에서 시작했으므로 0으로 돌아가는 거리를 반환한다
    if(dp[now][status] != INF) return dp[now][status];      // dp 배열의 값이 초깃값이 아니라면 이미 갱신됐다는 의미이기 때문에 바로 반환한다. 

    int iBit, cost;                         // iBit는 i번째 노드의 bit 표현 값, cost는 dfs의 반환값    
    for(int i = 0; i < N; i++) {            // N개의 노드만큼 반복
        iBit = (1 << i);                    // i번째 노드의 bit 표현 값
        if(status & iBit) continue;         // 이미 방문하고 있는 상태라면 continue 
        if(dist[now][i] == 0) continue;     // 거리가 0이라면 갈 수 없는 노드이다

        cost = dfs(i, status | iBit);       // dfs 호출
        if(cost) dp[now][status] = min(dp[now][status], cost + dist[now][i]);   // 최솟값으로 갱신
    }
    return dp[now][status];                 // dp 값 반환
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> N;
    finalStatus = (1 << N) - 1;             // 최종 상태 값 저장, if (N == 3) => 0111

    for(int i = 0; i < N; i++) {            // input
        for(int j = 0; j < N; j++) {
            cin >> dist[i][j];
        }
    }
    fill_n(dp[0], 16 * (1 << 16), INF);     // dp 배열 INF로 초기화
    cout << dfs(0, 1);                      // dfs 호출, 시작 노드는 0, 방문 상태는 0001
}