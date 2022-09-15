#include <string>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

#define INF (int)1e9

int dy[] = {-1, 0, 1, 0};
int dx[] = {0, 1, 0, -1};

int N;
int ans = INF;
int cost[26][26][4]; // dist[y][x][i] (y, x)에서 i 방향일 때 최소 비용

inline bool oor(int& y, int& x) {
    return (y < 0 || x < 0 || y >= N || x >= N); 
}

void dfs(int y, int x, int c, int d, vector<vector<int>>& board) {    
    if(y == N - 1 && x == N - 1) {
        ans = min(ans, c);
        return;
    }

    for(int i = 0; i < 4; i++) {

        int ny = y + dy[i];
        int nx = x + dx[i];

        if(oor(ny, nx) || board[ny][nx]) continue;

        int nc = c + 100;
        if(d != -1 && (i + d) % 2) nc += 500;

        if(cost[ny][nx][i] > nc) {
            cost[ny][nx][i] = nc;
            dfs(ny, nx, nc, i, board);
        }
    }

}

int solution(vector<vector<int>> board) {

    N = board.size();
    fill_n(cost[0][0], 26 * 26 * 4, INF);

    dfs(0, 0, 0, -1, board);
    return ans;
}


// 차이가 크진 않지만 채점 결과는 dijkstra가 더 빠르다.