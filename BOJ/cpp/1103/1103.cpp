#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

#define pii pair<int, int>
#define F first
#define S second
#define ll long long

#define endl '\n'

int N, M;
int map[51][51];
int dp[51][51][4];
bool visited[51][51];

int dy[] = {1, 0, -1, 0};
int dx[] = {0, 1, 0, -1};

int solve(int y, int x) {
    // 현재 위치가 방문해봤던 위치인지 검사
    if(visited[y][x]) return -1;

    // 최대값
    int maxCount = 0;
    
    // 혹시 현재 위치가 탐색해봤던 곳인지 확인
    for(int i = 0; i < 4; i++) {
        maxCount = max(maxCount, dp[y][x][i]);
    }

    // maxCount가 0이 아니라는 것은 탐색해봤던 위치라는 의미
    if(maxCount) {
        return maxCount;
    }

    // 방문한 적 없다면 1로 초기화 
    // 구멍에 빠지거나 범위를 벗어나도 현재 위치에서 한번은 움직일 수 있기 때문
    maxCount = 1;
    for(int i = 0; i < 4; i++) {
        dp[y][x][i] = 1;
    }

    // 방문 처리
    visited[y][x] = true;

    // 곱해지는 값
    int beta = map[y][x];

    // 방향 탐색
    for(int i = 0; i < 4; i++) {
        
        // 해당 방향으로의 다음 좌표 계산
        int ny = y + (dy[i] * beta);
        int nx = x + (dx[i] * beta);

        // 범위 확인, 구멍 확인
        if(ny < 0 || nx < 0 || ny >= N || nx >= M || !map[ny][nx]) continue;

        // 갈 수 있는 범위라면
        int count = solve(ny, nx);

        // 무한 반복이라면 종료
        if(count == -1) return -1;

        // 정상적이라면
        dp[y][x][i] += count;
        maxCount = max(dp[y][x][i], maxCount);
    }
    // 방문 처리 취소
    visited[y][x] = false;

    // 현재 위치에서의 최대값을 반환
    return maxCount;
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> N >> M;

    char tmp;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> tmp;

            if(tmp == 'H') map[i][j] = 0;
            else map[i][j] = tmp - '0';

            for(int k = 0; k < 4; k++) dp[i][j][k] = 0;

            visited[i][j] = false;
        }
    }
    cout << solve(0, 0);
}