#include <iostream>
using namespace std;

int N, M;
int map[500][500];
int dp[500][500];

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

inline bool rangeCheck(int y, int x) {
    return (y < 0 || y >= N || x < 0 || x >= M);
}

int dfs(int y, int x) {
    if(y == N - 1 && x == M - 1) return 1;
    else if(dp[y][x] != -1) return dp[y][x];

    dp[y][x] = 0;
    for(int i = 0; i < 4; i++) {
        int y_ = y + dy[i];
        int x_ = x + dx[i];

        if(rangeCheck(y_, x_)) continue;
        else if(map[y][x] <= map[y_][x_]) continue;

        dp[y][x] += dfs(y_, x_);
    }
    return dp[y][x];
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> map[i][j];
            dp[i][j] = -1;
        }
    }
    cout << dfs(0, 0);
}