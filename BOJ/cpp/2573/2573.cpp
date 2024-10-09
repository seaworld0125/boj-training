#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int N, M;
int map[301][301];
bool visited[301][301];

struct Data {
    int y;
    int x;
    int h;

    bool isVisited() {
        return visited[y][x];
    }
    bool melting() {
        map[y][x] -= h;
        h = 0;
        if(map[y][x] <= 0) {
            map[y][x] = 0;
            return true;
        }
        return false;
    }
    Data(int y, int x) : y(y), x(x) {}
};

int dy[] = {1, -1, 0, 0};
int dx[] = {0, 0, 1, -1};

void check(Data& data) {
    int count = 0;
    for(int i = 0; i < 4; i++) {
        int y = data.y + dy[i];
        int x = data.x + dx[i];

        if(y < 0 || x < 0 || y >= N || x >= M || map[y][x]) continue;

        count++;
    }
    data.h = count;
}

void dfs(int ny, int nx) {
    visited[ny][nx] = true;
    for(int i = 0; i < 4; i++) {
        int y = ny + dy[i];
        int x = nx + dx[i];

        if(y < 0 || x < 0 || y >= N || x >= M || visited[y][x] || map[y][x] == 0) continue;
    
        dfs(y, x);
    }
}

queue<Data> ice[2];
bool turn = false;

int solve() {
    int year = 0;

    while(1) {
        year++;
        vector<Data> meltingList;
        int size = ice[turn].size();    

        // 남은 얼음 없으면 종료
        if(!size) break;

        // 근처 0 개수 파악
        for(int i = 0; i < size; i++) {
            Data data = ice[turn].front();
            ice[turn].pop();

            // 녹아야하는 높이 저장
            check(data);
            meltingList.push_back(data);
        }

        // 방문 초기화
        memset(visited[0], 1, sizeof(visited));

        // 빙하 녹임
        for(auto& data : meltingList) {
            if(data.melting()) continue;

            // 다 안녹은 애들은 다음 큐에 삽입
            ice[!turn].push(data);
            visited[data.y][data.x] = false;
        }

        // 다음 큐
        turn = !turn;

        // 남은 얼음 없으면 종료
        if(ice[turn].empty()) break;

        // 남아있는 빙하 탐색
        dfs(ice[turn].front().y, ice[turn].front().x);

        // 아직도 방문하지 않은 빙하가 있다면 둘로 갈라진 것임
        while(!ice[turn].empty()) {
            Data data = ice[turn].front();

            if(!data.isVisited()) return year;

            ice[!turn].push(data);
            ice[turn].pop();
        }

        // 다음 큐
        turn = !turn;
    }
    return 0;
}

int main() {
    cin >> N >> M;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> map[i][j];

            if(map[i][j]) ice[turn].emplace(i, j);
        }
    }
    cout << solve();
}