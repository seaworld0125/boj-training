#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
int map[500][500];
int ans = 0;

int dy[4] = {-1,1,0,0};
int dx[4] = {0,0,1,-1};

vector<pair<int, int>> sp[] = {{{-1, 0}, {0, 1}, {1, 0}}, // ㅏ
                            {{0, -1}, {0, 1}, {1, 0}}, // ㅜ
                            {{-1, 0}, {0, -1}, {1, 0}}, // ㅓ
                            {{0, -1}, {-1, 0}, {0, 1}}}; // ㅗ

bool visited[500][500];

bool checkRange(int y, int x) {
    return (y < 0 || x < 0 || y >= N || x >= M);
}

void specialCase(int y, int x, int num) {
    for(int i = 0; i < 4; i++) {
        int sum = num;

        for(int j = 0; j < 3; j++) {
            int y_ = y + sp[i][j].first;
            int x_ = x + sp[i][j].second;
            if(checkRange(y_, x_)) break;

            sum += map[y_][x_];
        }
        ans = max(ans, sum);
    }
}

void dfs(int y, int x, int depth, int sum) {
    if(depth == 3) {
        ans = max(ans, sum);
        return;
    }

    visited[y][x] = true;
    for(int i = 0; i < 4; i++) {
        int y_ = y + dy[i];
        int x_ = x + dx[i];

        if(checkRange(y_, x_) || visited[y_][x_]) continue;


        dfs(y_, x_, depth + 1, sum + map[y_][x_]);
    }
    visited[y][x] = false;
}

int main() {
    cin >> N >> M;

    for(int i = 0; i < N; i++) 
        for(int j = 0; j < M; j++) 
            cin >> map[i][j];

    fill_n(visited[0], N * M, false);
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {

            specialCase(i, j, map[i][j]);
            dfs(i, j, 0, map[i][j]);
        }
    }
    cout << ans;
}