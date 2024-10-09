#include <iostream>
#include <queue>
using namespace std;

int L = 1, R = 1, C = 1; // 상범 빌딩의 층 수, 행, 열
int sl, sy, sx; // 출발 지점
int el, ey, ex; // 탈출 지점
char map[30][30][30]; // 층, 행, 열
bool visited[30][30][30];
/*
'#' 지나갈 수 없음
'.' 비어있음
'S' 시작 지점
'E' 탈출 지점
*/
int dl[] = {1, -1};
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

struct Pos {
    int l;
    int y;
    int x;
    Pos(int l, int y, int x) : l(l), y(y), x(x) {}
};

inline bool rangeCheck(int l, int y, int x) {
    return l < 0 || l >= L || y < 0 || y >= R || x < 0 || x >= C || map[l][y][x] == '#' || visited[l][y][x];
}

int BFS() {
    queue<Pos> visit;
    visit.emplace(sl, sy, sx);

    fill_n(visited[0][0], 27000, false);
    visited[sl][sy][sx] = true;
    int dist = -1;

    while(!visit.empty()) {
        dist++;

        int size = visit.size();
        for(int i = 0; i < size; i++) {
            Pos pos = visit.front();
            visit.pop();
                
            for(int k = 0; k < 4; k++) {
                int y = pos.y + dy[k];
                int x = pos.x + dx[k];

                if(rangeCheck(pos.l, y, x)) continue;
                if(pos.l == el && y == ey && x == ex) return dist + 1;

                visit.emplace(pos.l, y, x);
                visited[pos.l][y][x] = true;
            }
            for(int k = 0; k < 2; k++) {
                int l = pos.l + dl[k];

                if(rangeCheck(l, pos.y, pos.x)) continue;
                if(l == el && pos.y == ey && pos.x == ex) return dist + 1;

                visit.emplace(l, pos.y, pos.x);
                visited[l][pos.y][pos.x] = true;
            }
        }
    } 
    return 0;
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    while(1) {
        cin >> L >> R >> C;
        if(!(L | R | C)) break;

        for(int i = 0; i < L; i++) {
            for(int j = 0; j < R; j++) {
                for(int k = 0; k < C; k++) {
                    cin >> map[i][j][k];

                    if(map[i][j][k] == 'S') sl = i, sy = j, sx = k;
                    else if(map[i][j][k] == 'E') el = i, ey = j, ex = k;
                }
            }
        }
        int ans = BFS();
        if(ans) cout << "Escaped in " << ans << " minute(s).\n";
        else cout << "Trapped!\n";
    }
}