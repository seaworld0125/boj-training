#include <iostream>
#include <queue>
using namespace std;

#define F first
#define S second

int N, M, r, c;
int map[51][51];

int dir; // 북 0, 동 1, 남 2, 서 3
int dy[] = {-1, 0, 1, 0};
int dx[] = {0, 1, 0, -1};

bool checkRange(int y, int x) {
    return y < 0 || x < 0 || y >= N || x >= M;
}

int BFS() {
    bool visited[51][51];
    fill_n(visited[0], 51 * 51, false);
    visited[r][c] = true;

    queue<pair<int, int>> visit;
    visit.emplace(r, c);

    int cleanCount = 1;

    while(!visit.empty()) {
        auto pos = visit.front();
        visit.pop();
        
        bool cantClean = true;

        for(int i = 0; i < 4; i++) { // 한바퀴 돈다
            dir = (dir - 1 < 0 ? 3 : dir - 1); // 왼쪽 회전

            int y = pos.F + dy[dir];
            int x = pos.S + dx[dir];

            if(checkRange(y, x) || map[y][x] || visited[y][x]) continue;

            visit.emplace(y, x);
            visited[y][x] = true;
            cantClean = false;
            cleanCount++;
            break;
        }

        if(cantClean) { // 청소 못했다면 후진하거나 작동 멈춤 // 현재 후진이 안댐
            int backDir = (dir + 2) % 4;
            
            int y = pos.F + dy[backDir];
            int x = pos.S + dx[backDir];

            if(checkRange(y, x) || map[y][x]) continue;

            visit.emplace(y, x);
        }
    }
    return cleanCount;
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> N >> M;
    cin >> r >> c >> dir;
    r, c;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }
    cout << BFS();
}