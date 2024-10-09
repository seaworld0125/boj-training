#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

#define INF (int)1e9

// 동 남 서 북
int dir[] = {0, 1, 2, 3},
    dy[] = {0, 1, 0, -1},
    dx[] = {1, 0, -1, 0},
    H, 
    W;

pair<int, int> startPos[2];

char map[101][101];
int visited[101][101]; // 최소값을 저장

struct Data {
    int ny;
    int nx;
    int nDir;
    int nCost;
    Data(int y, int x, int d, int c) : ny(y), nx(x), nDir(d), nCost(c) {}
};

inline bool checkRange(int y, int x) { // 범위 체크
    return map[y][x] == '*' || y < 0 || x < 0 || y >= H || x >= W;
}

void BFS() {
    queue<Data> q;
    fill_n(visited[0], 101 * 101, INF);

    int sy = startPos[0].first;
    int sx = startPos[0].second;

    for(int i = 0; i < 4; i++) { // 출발 지점 네방향에서 시작
        q.emplace(sy, sx, i, 0); 
    }
    visited[sy][sx] = 0;

    while(!q.empty()) {
        auto pos = q.front();
        q.pop();

        for(int i = 0; i < 4; i++) {
            if(pos.nDir == ((i + 2) % 4)) continue;
            int y = pos.ny + dy[i];
            int x = pos.nx + dx[i];
            int cost = pos.nCost;

            if(checkRange(y, x)) continue; // 범위를 벗어난다면

            if(i != pos.nDir) cost++;
            if(visited[y][x] >= cost) {
                visited[y][x] = cost;
                q.emplace(y, x, i, cost);
            }
        }
    }
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> W >> H;

    for(int i = 0, c = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            cin >> map[i][j];

            if(map[i][j] == 'C') {
                startPos[c++] = {i, j};
            }
        }
    }
    BFS();
    cout << visited[startPos[1].first][startPos[1].second];
}