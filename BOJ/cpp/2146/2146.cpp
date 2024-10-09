#include <iostream>
#include <queue>
using namespace std;

#define F first
#define S second
#define INF (int)1e9

int N;
int map[101][101];

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

inline bool checkRange(int y, int x) {
    return y < 0 || y >= N || x < 0 || x >= N;
}   

int BFS(int y, int x, int islandNum) { // 다리 찾기
    queue<pair<int, int>> visit;
    visit.emplace(y, x);

    int visited[101][101];
    fill_n(visited[0], 10201, INF);
    visited[y][x] = 0;

    while(!visit.empty()) {
        auto pos = visit.front();
        visit.pop();

        for(int i = 0; i < 4; i++) {
            int y = pos.F + dy[i];
            int x = pos.S + dx[i];

            if(checkRange(y, x) || visited[y][x] != INF || map[y][x] == islandNum) continue;

            if(map[y][x]) {
                return visited[pos.F][pos.S];
            }
            visit.emplace(y, x);
            visited[y][x] = visited[pos.F][pos.S] + 1;
        }
    }
    return INF;
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> N;

    int count = 1;
    for(int i = 0; i < N; i++) { // 각각 번호 매기기
        for(int j = 0; j < N; j++) {
            cin >> map[i][j];

            if(map[i][j]) map[i][j] = count++;
        }
    }


    for(int i = 0; i < N; i++) { // 부모 번호로 통일하기
        for(int j = 0; j < N; j++) {
            if(map[i][j]) {
                
                queue<pair<int, int>> visit;
                visit.emplace(i, j);

                while(!visit.empty()) {
                    auto pos = visit.front();
                    visit.pop();

                    for(int i = 0; i < 4; i++) {
                        int y = pos.F + dy[i];
                        int x = pos.S + dx[i];

                        if(checkRange(y, x) || !map[y][x]) continue;
                        
                        if(map[y][x] > map[pos.F][pos.S]) {
                            map[y][x] = map[pos.F][pos.S];
                            visit.emplace(y, x);
                        }
                    }
                }
            }
        }
    }

    int ans = INF;
    for(int i = 0; i < N; i++) { // 가장 짧은 다리 찾기
        for(int j = 0; j < N; j++) {
            if(!map[i][j]) continue;

            ans = min(ans, BFS(i, j, map[i][j]));
        }
    }
    cout << ans;
}