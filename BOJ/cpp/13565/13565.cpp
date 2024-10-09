#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool map[1001][1001];
bool visited[1001][1001];
queue<pair<int, int>> visit;

int M, N;
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

inline bool checkRange(int y, int x) {
    return y < 0 || x < 0 || y >= M || x >= N || map[y][x];
}

void BFS() {
    fill_n(visited[0], 1002001, false);
    visited[visit.front().first][visit.front().second] = true;

    while(!visit.empty()) {
        auto pos = visit.front();
        visit.pop();

        int y, x;
        for(int i = 0; i < 4; i++) {
            y = pos.first + dy[i];
            x = pos.second + dx[i];

            if(visited[y][x] || checkRange(y, x)) continue;

            if(y == 0) {
                cout << "YES";
                return;
            }

            visited[y][x] = true;
            visit.emplace(y, x);
        }
    }
    cout << "NO";
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> M >> N;

    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++) {
            char n;
            cin >> n;
            map[i][j] = n - '0';

            if(i == M - 1 && !map[i][j]) 
                visit.emplace(i, j);
        }
    }
    if(visit.empty()) cout << "NO";
    else BFS();
}