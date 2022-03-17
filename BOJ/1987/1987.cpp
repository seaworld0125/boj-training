#include <iostream>
using namespace std;

char map[21][21];
int dy[] = {1, 0, -1, 0};
int dx[] = {0, 1, 0, -1};
int R, C;

inline bool checkRange(int y, int x) {
    return (y < 0 || x < 0 || y >= R || x >= C);
}

int DFS(int y, int x, bool * visited, int now) {
    int ans = now;
    for(int i = 0; i < 4; i++) {
        int y_ = y + dy[i];
        int x_ = x + dx[i];
        
        if(checkRange(y_, x_) || visited[map[y_][x_] - 'A'] || (y_ == 0 && x_ == 0)) continue;

        visited[map[y_][x_] - 'A'] = true;
        ans = max(ans, DFS(y_, x_, visited, now + 1));
        visited[map[y_][x_] - 'A'] = false;
    }
    return ans;
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> R >> C;

    for(int i = 0; i < R; i++)
        for(int j = 0; j < C; j++)
            cin >> map[i][j];

    bool visited[26];
    fill_n(visited, 26, false);
    visited[map[0][0] - 'A'] = true;

    cout << DFS(0, 0, visited, 1);
}