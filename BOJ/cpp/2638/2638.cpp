#include <iostream>
#include <queue>
using namespace std;

int N, M;
bool map[101][101];
int COUNT = 0;
queue<pair<int, int>> pos;

int dy[] = {0, 0, -1, 1};
int dx[] = {1, -1, 0, 0};

bool checkRange(int y, int x) {
    return y == 0 || x == 0 || y == N - 1 || x == M - 1;
}

bool BFS(int ny, int nx) {
    queue<pair<int, int>> visit;
    visit.emplace(ny, nx);

    bool visited[101][101];
    fill_n(visited[0], 10201, false);
    visited[ny][nx] = true;

    while(!visit.empty()) {
        int cy = visit.front().first;
        int cx = visit.front().second;
        visit.pop();

        if(checkRange(cy, cx)) return true;

        for(int i = 0; i < 4; i++) {
            int y = cy + dy[i];
            int x = cx + dx[i];

            if(map[y][x] || visited[y][x]) continue;

            visited[y][x] = true;
            visit.emplace(y, x);
        }
    }
    return false;
} 

void printMap() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cout << (map[i][j] ? '1' : '-') << ' ';
        }cout << endl;
    }cout << endl;
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> N >> M;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> map[i][j];

            if(map[i][j]) COUNT++;
        }
    }
    int ans = 0;
    while(COUNT) {
        ans++;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                if(map[i][j]) {
                    int airCount = 0, y, x;
                    for(int k = 0; k < 4; k++) {
                        y = i + dy[k];
                        x = j + dx[k];

                        if(map[y][x]) continue;

                        if(checkRange(y, x)) {
                            airCount++;
                        }
                        else if(BFS(y, x)) {
                            airCount++;
                        }
                    }
                    if(airCount >= 2) {
                        pos.emplace(i, j);
                    }
                }
            }
        }
        while(!pos.empty()) {
            map[pos.front().first][pos.front().second] = false;
            COUNT--;
            pos.pop();
        }
    }
    cout << ans;
}