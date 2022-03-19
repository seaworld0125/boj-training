#include <iostream>
#include <queue>
using namespace std;

int N, M;
int map[100][100];
int dp[100][100];

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

inline bool checkRange(int y, int x) {
    return (y < 0 || x < 0 || y >= N || x >= M);
}

void dijkstra() {
    priority_queue<pair<int, pair<int, int>>> pq;
    pq.push({0, {0, 0}}); // dist, y, x

    while(!pq.empty()) {
        int dist = -pq.top().first;
        auto pos = pq.top().second;
        pq.pop();

        if(dp[pos.first][pos.second] < dist) continue;

        for(int i = 0; i < 4; i++) {
            int y = pos.first + dy[i];
            int x = pos.second + dx[i];

            if(checkRange(y, x)) continue;

            int cost = dist + map[y][x];

            if(cost < dp[y][x]) {
                dp[y][x] = cost;
                pq.push({-cost, {y, x}});
            }
        }
    }
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> M >> N;
    fill_n(dp[0], 10000, (int)1e9);

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            char c;
            cin >> c;
            map[i][j] = c - '0';
        }
    }

    if((M + N == 2) || (M + N == 3)) {
        cout << 0;
        return 0;
    }
    dijkstra();
    cout << dp[N - 1][M - 1];
}