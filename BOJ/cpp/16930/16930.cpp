#include <iostream>
#include <queue>
using namespace std;

#define F first
#define S second
#define INF (int)1e9

int N, M, K, startY, startX, endY, endX, dp[1001][1001];
char map[1001][1001];
queue<pair<int, int>> visit;

int dy[] = {0, 0, 1, -1};
int dx[] = {1, -1, 0, 0};

inline bool checkRange(int y, int x) {
    return y < 1 || x < 1 || y > N || x > M || map[y][x] == '#';
}

void BFS() {
    visit.emplace(startY, startX);
    dp[startY][startX] = 0;

    while(!visit.empty()) {
        auto pos = visit.front();
        visit.pop();

        for(int i = 0; i < 4; i++) { // 방향을 정한다
            int y = pos.first;
            int x = pos.second;

            for(int j = 0; j < K; j++) { // 해당 방향으로 직진
                y += dy[i];
                x += dx[i];                

                if(checkRange(y, x) || dp[y][x] < dp[pos.F][pos.S] + 1) break; // 해당 방향으로 진행이 가능한지 확인한다.

                if(dp[y][x] == INF) { // 방문하지 않았다면
                    dp[y][x] = dp[pos.F][pos.S] + 1;
                    visit.emplace(y, x);
                }
            }
        }
    }
}

int main() {ios_base::sync_with_stdio(0);cin.tie(NULL);
    cin >> N >> M >> K;

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cin >> map[i][j];
            dp[i][j] = INF;
        }
    }
    cin >> startY >> startX >> endY >> endX;

    BFS();
    if(dp[endY][endX] != INF) cout << dp[endY][endX];
    else cout << -1;
}