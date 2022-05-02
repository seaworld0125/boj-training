#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define INF (int)1e9

int n,
    map[501][501],
    dp[501][501];

int dy[] = {1, -1, 0, 0};
int dx[] = {0, 0, -1, 1};

int recursive(int y, int x) {

    if(dp[y][x]) { // 이전에 탐색했었다면 해당 값을 반환
        return dp[y][x];
    }
    dp[y][x] = 1;

    for(int i = 0; i < 4; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];

        if(ny < 0 || nx < 0 || ny >= n || nx >= n || map[y][x] >= map[ny][nx]) continue;

        dp[y][x] = max(dp[y][x], recursive(ny, nx) + 1); // 현재 위치에서의 최대값을 구함
    }
    return dp[y][x];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);
    
    cin >> n;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> map[i][j];
        }
    }
    memset(dp[0], 0, sizeof(dp));

    int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            ans = max(ans, recursive(i, j));
        }
    }
    cout << ans;
}