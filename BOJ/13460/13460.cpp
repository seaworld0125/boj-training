// 기울이는 동작은 벽에 부딪힐 때 까지 지속된다

#include <iostream>
#include <queue>
using namespace std;

#define INF (int)1e9
#define F first
#define S second

int N, M;
pair<int, int> startR, startB;

char board[10][10];
bool visited[10][10][10][10];

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

bool checkRange(int y, int x) {
    return (y < 0 || x < 0 || y >= N || x >= M);
}

struct INFO { 
    int ry;
    int rx;
    int by;
    int bx;
    int cnt;

    INFO(int ry, int rx, int by, int bx, int c) : ry(ry), rx(rx), by(by), bx(bx), cnt(c) {}
};

int findRoot() {
    int ry = startR.F;
    int rx = startR.S;
    int by = startB.F;
    int bx = startB.S;

    queue<INFO> q;
    q.emplace(ry, rx, by, bx, 0);
    visited[ry][rx][by][bx] = true;

    int ans = -1;
    while(!q.empty()) {
        int ry_ = q.front().ry;
        int rx_ = q.front().rx;
        int by_ = q.front().by;
        int bx_ = q.front().bx;
        int cnt_ = q.front().cnt;
        q.pop();

        if(cnt_ > 10) {
            ans = -1;
            break;
        }
        if(board[ry_][rx_] == 'O' && board[by_][bx_] != 'O') {
            ans = cnt_;
            break;
        }

        for(int i = 0; i < 4; i++) {
            int nry = ry_;
            int nrx = rx_;
            int nby = by_;
            int nbx = bx_;

            while(1) { // R 구슬 이동
                if(board[nry][nrx] != '#' && board[nry][nrx] != 'O') {
                    nry += dy[i], nrx += dx[i];
                }
                else {
                    if(board[nry][nrx] == '#') {
                        nry -= dy[i], nrx -= dx[i];
                    }
                    break;
                }
            }
            while(1) { // B 구슬 이동
                if(board[nby][nbx] != '#' && board[nby][nbx] != 'O') {
                    nby += dy[i], nbx += dx[i];
                }
                else {
                    if(board[nby][nbx] == '#') {
                        nby -= dy[i], nbx -= dx[i];
                    }
                    break;
                }
            }

            if(nry == nby && nrx == nbx) { // 구슬 위치가 같을 때 예외 처리
                if(board[nry][nrx] != 'O') {
                    int rdist = abs(nry - ry_) + abs(nrx - rx_);
                    int bdist = abs(nby - by_) + abs(nbx - bx_);

                    if(rdist > bdist) {
                        nry -= dy[i], nrx -= dx[i];
                    }
                    else {
                        nby -= dy[i], nbx -= dx[i];
                    }
                }
            }

            if(visited[nry][nrx][nby][nbx]) continue;

            visited[nry][nrx][nby][nbx] = true;
            q.emplace(nry, nrx, nby, nbx, cnt_ + 1);
        }
    }
    return ans;
}

int main() {
    cin >> N >> M;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> board[i][j];

            if(board[i][j] == 'R') startR = {i, j};
            else if(board[i][j] == 'B') startB = {i, j};
        }
    }
    fill_n(visited[0][0][0], 10000, false);

    cout << findRoot();
}