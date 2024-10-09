#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

#define INF (int)1e9

int K, W, H;
int ans = INF;
int map[201][201];

int dy[] = {1, -1, 0, 0};
int dx[] = {0, 0, 1, -1};

int jy[] = {1, 1, -1, -1, 2, 2, -2, -2};
int jx[] = {2, -2, 2, -2, 1, -1, 1, -1};

struct Info {
    int y;
    int x;
    int jump;
    int dist;
    Info(int y, int x, int j, int c) : y(y), x(x), jump(j), dist(c) {}
};

// (y, x, 움직인 횟수)
void BFS() {
    queue<Info> visit;
    bool visited[201][201][31];

    visit.emplace(0, 0, K, 0);
    memset(visited, 0, sizeof(visited));
    visited[0][0][K] = true;

    while(!visit.empty()) {

        int size = visit.size();
        for(int i = 0; i < size; i++) {

            auto info = visit.front();
            visit.pop();

            if((info.y == H - 1) && (info.x == W - 1)) {
                ans = min(ans, info.dist);
                continue;
            }

            int y, x;

            // 점프할 수 있음
            if(info.jump) {
                for(int j = 0; j < 8; j++) {

                    y = info.y + jy[j];
                    x = info.x + jx[j];

                    if(y < 0 || x < 0 || y >= H || x >= W || map[y][x] || visited[y][x][info.jump - 1]) continue;
                     
                    visit.emplace(y, x, info.jump - 1, info.dist + 1);
                    visited[y][x][info.jump - 1] = true;
                }
            }

            for(int j = 0; j < 4; j++) {

                y = info.y + dy[j];
                x = info.x + dx[j];

                if(y < 0 || x < 0 || y >= H || x >= W || map[y][x] || visited[y][x][info.jump]) continue;
                    
                visit.emplace(y, x, info.jump, info.dist + 1);
                visited[y][x][info.jump] = true;
            }
        }
    }
}
 
int main() {
    cin >> K >> W >> H;

    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            cin >> map[i][j];
        }
    }
    BFS();
    cout << (ans == INF ? -1 : ans);
}