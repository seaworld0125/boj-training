#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define pii pair<int, int>
#define F first
#define S second

int R, C, ans = 0;
bool meet = false;
bool visited[1501][1501];

char map[1501][1501];
queue<pii> ice;
queue<pii> swan;
queue<pii> swanNext;

int dy[] = {0, 0, -1, 1};
int dx[] = {-1, 1, 0, 0};

bool checkRange(int y, int x) {
    return y < 0 || x < 0 || y >= R || x >= C;
}

void swanBFS() {
    int ny, nx, y, x;
    while(!swan.empty()) {
        ny = swan.front().F;
        nx = swan.front().S;
        swan.pop();
        for(int j = 0; j < 4; j++) {
            y = ny + dy[j];
            x = nx + dx[j];

            if(checkRange(y, x) || visited[y][x]) continue;

            if(map[y][x] == 'L') {
                meet = true;
                return;
            }
            else if(map[y][x] == 'X') {
                swanNext.emplace(y, x);
                visited[y][x] = true;
            }
            else {
                swan.emplace(y, x);
                visited[y][x] = true;
            }
        }
    }
}

void iceBFS() {
    int size = ice.size();
    int ny, nx, y, x;
    for(int i = 0; i < size; i++) {
        ny = ice.front().F;
        nx = ice.front().S;
        ice.pop();

        for(int j = 0; j < 4; j++) {
            y = ny + dy[j];
            x = nx + dx[j];

            if(checkRange(y, x)) continue;

            if(map[y][x] == 'X') {
                map[y][x] = '.';
                ice.emplace(y, x);
            }
        }
    }
}

void input() {
    fill_n(visited[0], 1501 * 1501, false);
    
    cin >> R >> C; 
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cin >> map[i][j];

            if(map[i][j] != 'X') ice.emplace(i, j);
            if(swan.empty() && map[i][j] == 'L') {
                swan.emplace(i, j);
                visited[i][j] = true;
            }
        }
    }
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    input();

    while(1) {
        swanBFS();
        if(meet) {
            cout << ans;
            break;
        }
        swanNext.swap(swan);
        queue<pii>().swap(swanNext);
        iceBFS();
        ans++;
    }
}