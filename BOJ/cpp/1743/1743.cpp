#include <iostream>
#include <queue>
using namespace std;

#define F first
#define S second

int N, M, K;
int r, c;
bool map[101][101];
int dy[] = {1, -1, 0, 0};
int dx[] = {0, 0, -1, 1};

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> N >> M >> K;

    fill_n(map[0], 10201, false);

    for(int i = 0; i < K; i++) {
        cin >> r >> c;
        map[r - 1][c - 1] = true;
    }

    int ans = 0;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {

            if(!map[i][j]) continue;

            queue<pair<int, int>> visit;
            visit.emplace(i, j);
            map[i][j] = false;

            int count = 0;

            while(!visit.empty()) {
                auto pos = visit.front();
                visit.pop();
                count++;
 
                for(int i = 0; i < 4; i++) {
                    int y = pos.F + dy[i];
                    int x = pos.S + dx[i];

                    if(y < 0 || y >= N || x < 0 || x >= M || !map[y][x]) continue;

                    visit.emplace(y, x);
                    map[y][x] = false;
                }
            }
            ans = max(ans, count);
        }
    }
    cout << ans;
}