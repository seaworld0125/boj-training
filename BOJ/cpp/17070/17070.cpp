#include <iostream>
using namespace std;

int N;
int ans = 0;
int map[17][17];

int dir = 0; // 0 = 가로, 1 = 우대각, 2 = 아래
int dy[] = {0, 1, 1};
int dx[] = {1, 1, 0};

int dp[3][17][17]; // 어떤 방향에서 진행해왔는지

bool checkWallpaper(int y, int x, int dir);
bool checkRange(int y, int x);
int move(int y, int x, int dir);
int recursive(int y, int x, int dir);

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> N;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> map[i][j];

            for(int k = 0; k < 3; k++) dp[k][i][j] = 0;
        }
    }

    ans += recursive(0, 1, 0);

    cout << ans;
}

bool checkWallpaper(int y, int x) {
    return map[y][x - 1] || map[y - 1][x];
}

bool checkRange(int y, int x) {
    return y < 0 || x < 0 || y >= N || x >= N || map[y][x];
}

int move(int y, int x, int dir) {
    if(checkRange(y, x)) return 0;
    if(dir == 1 && checkWallpaper(y, x)) return 0;
    return recursive(y, x, dir);
}

int recursive(int y, int x, int dir) {
    if(x == N - 1 && y == N - 1) {
        return 1;
    } 
    if(dp[dir][y][x]) { // 이미 가본 적 있다면
        return dp[dir][y][x];
    } 
    int ny, nx;
    if(dir == 0) {
        dp[dir][y][x] += move(y + dy[0], x + dx[0], 0);
        dp[dir][y][x] += move(y + dy[1], x + dx[1], 1);
    }
    else if(dir == 1) {
        dp[dir][y][x] += move(y + dy[0], x + dx[0], 0);
        dp[dir][y][x] += move(y + dy[1], x + dx[1], 1);
        dp[dir][y][x] += move(y + dy[2], x + dx[2], 2);
    }
    else {
        dp[dir][y][x] += move(y + dy[1], x + dx[1], 1);
        dp[dir][y][x] += move(y + dy[2], x + dx[2], 2);
    }
    return dp[dir][y][x];
}