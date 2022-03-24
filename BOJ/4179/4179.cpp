#include <iostream>
#include <queue>
using namespace std;
#define INF (int)1e9

int R, C;
int jy, jx;
int fy, fx;

char map[1001][1001];
bool visited[1001][1001];
queue<pair<int, int>> visit;

inline bool checkRange(int y, int x) {
    return y < 0 || x < 0 || y >= R || x >= C || map[y][x] == '#' || map[y][x] == 'F';
}

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

int BFS() {
    fill_n(visited[0], 1002001, false);
    visit.emplace(fy, fx);
    visit.emplace(jy, jx);

    int ans = 1;
    while(!visit.empty()) {

        int size = visit.size();
        for(int i = 0; i < size; i++) {
            auto pos = visit.front();
            visit.pop();

            int y, x;
            for(int i = 0; i < 4; i++) {
                y = pos.first + dy[i];
                x = pos.second + dx[i];

                if(visited[y][x] || checkRange(y, x)) continue;

                if(map[pos.first][pos.second] == 'J') {
                    map[pos.first][pos.second]
                }

                visited[y][x] = true;
                visit.emplace(y, x);
            }
        }
        ans++;
    }
    return INF;
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> R >> C;

    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cin >> map[i][j];

            if(map[i][j] == 'J') {
                jy = i;
                jx = j;
            }
            else if(map[i][j] == 'F') {
                fy = i;
                fx = j;
            }
        }
    }
}