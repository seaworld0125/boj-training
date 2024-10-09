#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define F first
#define S second

int N, M;
int map[20][20];
pair<int, int> goal[402];

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

struct Taxi {
    int y;
    int x;
    int FUEL;
} taxi;

bool checkRange(int y, int x) {
    return y < 0 || x < 0 || y >= N || x >= N || map[y][x] == 1;
}

bool findGoal(int sy, int sx) {
    bool visited[20][20];
    fill_n(visited[0], 400, false);
    visited[sy][sx] = true;

    int goalY = goal[map[sy][sx]].F,
        goalX = goal[map[sy][sx]].S;
    map[sy][sx] = 0; // 손님 태웠으니 맵에서 지움

    queue<pair<int, int>> q;
    q.emplace(sy, sx);

    int size, dist = -1;
    while(!q.empty()) {
        size = q.size();
        dist++;

        for(int i = 0; i < size; i++) {
            auto pos = q.front();
            q.pop();

            for(int j = 0; j < 4; j++) {
                int y = pos.F + dy[j];
                int x = pos.S + dx[j];

                if(checkRange(y, x) || visited[y][x]) continue;

                if(y == goalY && x == goalX) {     // 목적지라면?
                    taxi.FUEL -= (dist + 1);            // 거리만큼 일단 기름 줄임
                    if(taxi.FUEL < 0) return false;     // 목적지까지 갈 수 없음       

                    taxi.FUEL += (dist + 1) * 2;        // 기름 충전
                    taxi.y = goalY;                     // 택시 위치 이동
                    taxi.x = goalX;
                    return true;
                }
                q.emplace(y, x);
                visited[y][x] = true;
            }
        }   
    }
    return false; // 여기까지 왔다는 건 목적지를 갈 수 없다는 의미
}

bool findGuest() {
    if(map[taxi.y][taxi.x] > 1) {           // 택시랑 손님 같은 위치인지 확인 필요
        M--;                                // 태웠으니 손님 수를 줄임
        return findGoal(taxi.y, taxi.x);    // 목적지로 택시 출발..// 결과 반환
    }
    queue<pair<int, int>> q;
    q.emplace(taxi.y, taxi.x);

    bool visited[20][20];
    fill_n(visited[0], 400, false);
    visited[taxi.y][taxi.x] = true;

    int size, dist = -1;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // 태우러 갈 수 있는 손님 위치 저장
    while(!q.empty()) {
        size = q.size();
        dist++;

        for(int i = 0; i < size; i++) {
            auto pos = q.front();
            q.pop();

            for(int j = 0; j < 4; j++) {
                int y = pos.F + dy[j];
                int x = pos.S + dx[j];

                if(checkRange(y, x) || visited[y][x]) continue;
                
                if(map[y][x] > 1) pq.emplace(y, x); // 손님이라면
                q.emplace(y, x);
                visited[y][x] = true;
            }
        }   
        if(pq.size()) {                         // 가까운 손님 찾음
            taxi.FUEL -= (dist + 1);            // 손님까지의 거리만큼 연료를 줄임
            if(taxi.FUEL <= 0) return false;    // 가까운 손님을 태우러 갈 수 없음..// 태우러 가도 목적지까지 갈 기름이 부족

            M--;                    // 태우러 갈 수 있으니 전체 손님 수를 줄임
            taxi.y = pq.top().F;    // 손님 위치로 택시 이동
            taxi.x = pq.top().S;

            return findGoal(taxi.y, taxi.x);    // 목적지로 택시 출발 // 결과 반환
        }
    }
    if(pq.empty() && M > 0)         // 손님이 남아있는데 태우러 갈 수 있는 손님이 없다면
        return false;               
}

int main() {
    cin >> N >> M >> taxi.FUEL;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }
    cin >> taxi.y >> taxi.x;
    taxi.y--;
    taxi.x--;

    int y, x, y_, x_;
    for(int i = 0, j = 2; i < M; i++, j++) {
        cin >> y >> x >> y_ >> x_;
        
        map[y - 1][x - 1] = j;
        goal[j] = {y_- 1, x_- 1};
    }

    while(M && findGuest()) {}

    if(M) cout << -1;
    else cout << taxi.FUEL;
}