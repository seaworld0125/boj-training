#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

int N, M, robotY, robotX, robotDir, goalY, goalX, goalDir;

int map[101][101];
int dp[101][101][101];

// 동 남 서 북
int dy[] = {0, 1, 0, -1}; 
int dx[] = {1, 0, -1, 0};

enum { 
    EAST, SOUTH, WEST, NORTH
};

// 로봇의 움직임을 저장
struct Info {
    int y;
    int x;
    int dir;
    int orderCount;
    Info(int y, int x, int d, int o) : y(y), x(x), dir(d), orderCount(o) {}
};

// 방문할 수 있는지 여부를 반환
bool checkRange(int y, int x) {
    return y < 1 || x < 1 || y > M || x > N || map[y][x];
}

// 방향 전환에 필요한 명령의 수 반환
int dirOrderCount(int dir, int toDir) {
    int sub = abs(dir - toDir); 

    if(sub == 2) return 2;
    else if(sub == 1 || sub == 3) return 1;
    else return 0;
}

bool checkGoal(int y, int x, int dir) {
    return y == goalY && x == goalX && dir == goalDir;
}

int BFS() {
    queue<Info> q;
    q.emplace(robotY, robotX, robotDir, 0);

    fill_n(dp[0][0], 1030301, (int)1e9);
    dp[robotY][robotX][robotDir] = 0;

    int ans = (int)1e9;

    while(!q.empty()) {
        auto info = q.front();
        q.pop();

        int y, x, orderCount;
        for(int i = 0; i < 4; i++) {
            // i 방향으로 회전하는데 필요한 명령어 수 더하기 // 즉 회전을 했다고 볼 수 있음
            orderCount = info.orderCount + dirOrderCount(info.dir, i); 
            
            // 회전 후 현재 위치와 방향이 목적지라면 갱신하고 더 이상 진행하지 않음
            if(checkGoal(info.y, info.x, i)) {
                ans = min(ans, orderCount);
                continue;
            }
            // 회전을 했지만 목적지가 아니기 때문에 계속 진행
            // 1,2,3 칸 이동했을 때 모두 확인 // 1~3 칸은 한 번에 이동할 수 있는 거리이기 때문
            y = info.y;
            x = info.x;
            orderCount++; // 직진 명령어 추가
            for(int j = 0; j < 3; j++) {
                y += dy[i]; 
                x += dx[i];
                // 더 이상 진행할 수 없으면 continue
                if(checkRange(y, x)) break;
                // 이미 더 짧은 경로가 갱신되어 있으면 continue
                if(dp[y][x][i] < orderCount) break;
                // 갱신
                dp[y][x][i] = orderCount;
                q.emplace(y, x, i, orderCount);
            }
        }
    }
    return ans;
}

void changeDirExp(int& dir) {
    dir--;
    if(dir == 2) dir = 1;
    else if(dir == 1) dir = 2;
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> M >> N;

    for(int i = 1; i <= M; i++) {
        for(int j = 1; j <= N; j++) {
            cin >> map[i][j];
        }
    }
    cin >> robotY >> robotX >> robotDir;
    cin >> goalY >> goalX >> goalDir;

    changeDirExp(robotDir);
    changeDirExp(goalDir);

    cout << BFS();
}