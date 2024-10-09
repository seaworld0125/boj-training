#include <iostream>
using namespace std;

#define F first
#define S second

int T, M, N, K, y, x, ans; // 테케, 가로, 세로, 배추 개수, pos
bool map[50][50];
pair<int, int> pos[2500];

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

inline bool checkRange(int y, int x) {
    return y < 0 || x < 0 || y >= N || x >= M;
}

void recursive(int y, int x) {
    if(map[y][x]) return;

    K--; // 방문
    map[y][x] = true;

    for(int i = 0; i < 4; i++) {
        int y_ = y + dy[i];
        int x_ = x + dx[i];

        if(checkRange(y_, x_) || map[y_][x_]) continue;
        recursive(y_, x_);
    }
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> T;

    while(T--) {
        cin >> M >> N >> K;

        fill_n(map[0], 2500, true);
        ans = 0;

        for(int i = 0; i < K; i++) {
            cin >> x >> y;
            map[y][x] = false;
            pos[i] = {y, x};
        }

        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                if(!map[i][j]) {
                    recursive(i, j);
                    ans++;
                }
            }
        }
        cout << ans << '\n';
    }
}