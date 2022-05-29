#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

#define pii pair<int, int>
#define F first
#define S second
#define endl '\n'

int T, w, h;
char map[1001][1001];

queue<pii> human;
queue<pii> fire;
bool visited[1001][1001];

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void solve() {
    int ans = 0;

    while(!human.empty()) {
        ans++;
        
        int size = fire.size();
        for(int i = 0; i < size; i++) {
            auto pos = fire.front();
            fire.pop();

            for(int j = 0; j < 4; j++) {
                int y = pos.F + dy[j];
                int x = pos.S + dx[j];

                if(y < 0 || x < 0 || y >= h || x >= w || map[y][x] == '*' || map[y][x] == '#') continue;

                map[y][x] = '*';
                fire.emplace(y, x);
            }
        }

        size = human.size();
        for(int i = 0; i < size; i++) {
            auto pos = human.front();
            human.pop();

            for(int j = 0; j < 4; j++) {
                int y = pos.F + dy[j];
                int x = pos.S + dx[j];

                if(y < 0 || x < 0 || y >= h || x >= w || map[y][x] != '.' || visited[y][x]) continue;

                if(y == 0 || x == 0 || y == h - 1 || x == w - 1) {
                    cout << ans + 1 << endl;
                    return;
                }
                visited[y][x] = true;
                human.emplace(y, x);
            }
        }
    }
    cout << "IMPOSSIBLE\n";
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> T;

    while(T--) {
        cin >> w >> h;

        queue<pii>().swap(human);
        queue<pii>().swap(fire);
        memset(visited[0], 0, sizeof(visited));

        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++) {
                cin >> map[i][j];

                if(map[i][j] == '@') {
                    human.emplace(i, j);
                    visited[i][j] = true;
                }
                else if(map[i][j] == '*') {
                    fire.emplace(i, j);
                }
            }
        }
        auto pos = human.front();
        if(pos.F == 0 || pos.S == 0 || pos.F == h - 1 || pos.S == w - 1) {
            cout << "1\n";
        }
        else {
            solve();
        }
    }
}