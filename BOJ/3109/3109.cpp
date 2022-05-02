#include <iostream>
#include <cstring>
using namespace std;

int R, C, ans = 0;
bool visited[10001][501];
char map[10001][501];

int dy[] = {-1, 0, 1}; // 위 - 직진 - 아래
int dx[] = {1, 1, 1};

inline bool checkRange(int y, int x) {
    return x < 0 || x >= C || y < 0 || y >= R;
}

bool counting(int y, int x) {
    visited[y][x] = true;
    if(x == C - 1) {
        ans++;
        return true;
    }

    for(int i = 0; i < 3; i++) {    
        int ny = y + dy[i];
        int nx = x + dx[i];

        if(checkRange(ny, nx)) continue;
        if(map[ny][nx] == 'x' || visited[ny][nx]) continue;

        if(counting(ny, nx)) return true;
    }
    return false;
}

int main() {
    cin >> R >> C; 

    // 0 ~ C - 1
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cin >> map[i][j];
        }
    }

    memset(visited[0], 0, sizeof(visited));

    for(int i = 0; i < R; i++) {
        counting(i, 0);
    }
    cout << ans;
}