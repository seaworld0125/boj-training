#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

#define F first
#define S second

int T, h, w;
char map[101][101];
int dp[101][101][2];
bool visited[101][101][2];
pair<int, int> prisoner[2];
vector<int> exitCost[2];

int dy[] = {1, 0, -1, 0};
int dx[] = {0, 1, 0, -1};

inline bool checkRange(int y, int x) {
    return y < 0 || x < 0 || y >= h || x >= w || map[y][x] == '*';
}

inline bool checkEnd(int y, int x, int prisonerNumber) {
    if(y == 0 || x == 0 || y == h - 1 || x == w - 1) {
        exitCost[prisonerNumber].emplace_back(dp[y][x][prisonerNumber]);
        return true;
    }
    return false;
}

inline int getAns() {
    sort(exitCost[0].begin(), exitCost[0].end());
    sort(exitCost[1].begin(), exitCost[1].end());
    cout << exitCost[0][0] << endl;
    cout << exitCost[1][0] << endl;
    cout << exitCost[0][0] + exitCost[1][0] << endl;

    cout << endl;
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            int num = dp[i][j][0];
            if(num == (int)1e9) cout << " \t";
            else cout << num << '\t';
        }cout << endl;
    }
    cout << endl;
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            int num = dp[i][j][1];
            if(num == (int)1e9) cout << " \t";
            else cout << num << '\t';
        }cout << endl;
    }
}

void BFS() {
    queue<pair<int, pair<int, int>>> q;
    q.push({0, {prisoner[0].F, prisoner[0].S}});
    q.push({1, {prisoner[1].F, prisoner[1].S}});

    dp[prisoner[0].F][prisoner[0].S][0] = 0;
    dp[prisoner[1].F][prisoner[1].S][1] = 0;

    visited[prisoner[0].F][prisoner[0].S][0] = true;
    visited[prisoner[1].F][prisoner[1].S][1] = true;

    while(!q.empty()) {
        auto pos = q.front();
        q.pop();

        for(int i = 0; i < 4; i++) {
            int y = pos.S.F + dy[i];
            int x = pos.S.S + dx[i];

            if(checkRange(y, x) || visited[y][x][pos.F]) continue;
            visited[y][x][pos.F] = true;

            if(map[y][x] == '#') { // 문을 만났을 때
                dp[y][x][pos.F] = dp[pos.S.F][pos.S.S][pos.F] + 1;
                map[y][x] = '.';
            }
            else { // 그냥 길
                dp[y][x][pos.F] = min(dp[y][x][(pos.F + 1) % 2], dp[pos.S.F][pos.S.S][pos.F]);
            }

            if(checkEnd(y, x, pos.F)) continue;
            q.push({pos.F, {y, x}});
        }
    }
}

void input() {
    cin >> h >> w;

    exitCost[0].clear();
    exitCost[1].clear();

    fill_n(dp[0][0], 20402, (int)1e9);
    fill_n(visited[0][0], 20402, false); 

    int prisonerCount = 0;
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            cin >> map[i][j];
            
            if(map[i][j] == '$') {
                prisoner[prisonerCount] = {i, j};
                prisonerCount++; 
            }
        }
    }
}

int main() {
    cin >> T;

    for(int i = 0; i < T; i++) {
        input();
        BFS();
        getAns();
    }
}