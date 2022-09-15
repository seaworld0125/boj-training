#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define INF (int)1e9

int dy[] = {-1, 0, 1, 0};
int dx[] = {0, 1, 0, -1};

int N;
int dist[26][26]; // dist[y][x]에서 dist[ny][nx]로 가는 최단 비용

struct Pos {
    int cost;
    int y;
    int x;
    int dir;

    Pos(int c, int y_, int x_, int d):cost(c), y(y_), x(x_), dir(d) {}
    
    bool operator<(const Pos& p) const {
        return cost < p.cost;
    }
};

inline bool oor(int& y, int& x) {
    return (y < 0 || x < 0 || y >= N || x >= N); 
}

int dijkstra(vector<vector<int>>& board) {

    priority_queue<Pos> pq;

    dist[0][0] = 0;
    pq.emplace(0, 0, 0, -1);

    while(!pq.empty()) {

        auto cost = pq.top().cost;
        auto y = pq.top().y;
        auto x = pq.top().x;
        auto dir = pq.top().dir;
        pq.pop();

        if(dist[y][x] < cost) continue;

        for(int i = 0; i < 4; i++) {

            int ny = y + dy[i];
            int nx = x + dx[i];

            if(oor(ny, nx) || board[ny][nx]) continue;

            int nc = cost + (dir == i ? 100 : 600);
            if(dir == -1) nc = 100;

            if(dist[ny][nx] >= nc) {
                dist[ny][nx] = nc;
                pq.emplace(nc, ny, nx, i);
            }
        }
    }
    return dist[N - 1][N - 1];
}

int solution(vector<vector<int>> board) {

    N = board.size();
    fill_n(dist[0], 26 * 26, INF);
    return dijkstra(board);
}