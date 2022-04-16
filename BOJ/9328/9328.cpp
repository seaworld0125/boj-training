#include <iostream>
#include <queue>
#include <string>
using namespace std;

#define INF (int)1e9

int T, h, w, status, ans;
char map[100][100];
bool visited[100][100];
vector<queue<pair<int, int>>> visitPos;

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, 1, -1};

inline bool checkRange(int y, int x) {
    return y < 0 || y >= h || x < 0 || x >= w;
}

inline bool isUpperCase(char& c) {
    return 'A' <= c && c <= 'Z';
}

inline bool isLowerCase(char& c) {
    return 'a' <= c && c <= 'z';
}

inline bool haskey(int idx) {
    return status & (1 << idx);
}

inline void plusKey(int idx) {
    status |= (1 << idx);
}

void dfs(int y, int x) {
    if(isUpperCase(map[y][x])) { // 대문자라면
        int idx = map[y][x] - 'A';

        if(!haskey(idx)) { // 키가 없다면
            visitPos[idx].emplace(y, x); // 방문 예정 목록에 추가
            return;
        }
    }
    else if(isLowerCase(map[y][x])) { // 소문자라면
        int idx = map[y][x] - 'a';
        plusKey(idx); // 키를 합침

        while(!visitPos[idx].empty()) { // 새로 생긴 키로 방문할 수 있는 위치가 있는지 확인
            int qy = visitPos[idx].front().first;
            int qx = visitPos[idx].front().second;
            visitPos[idx].pop();
            dfs(qy, qx);
        }
    }
    else if(map[y][x] == '$') { // 문서라면
        ans++;
    }
    visited[y][x] = true; // 방문처리

    for(int i = 0; i < 4; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];

        if(checkRange(ny, nx) || map[ny][nx] == '*' || visited[ny][nx]) continue;

        dfs(ny, nx);
    }
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> T;

    for(int i = 0; i < T; i++) {
        cin >> h >> w;

        queue<pair<int, int>> startPos;

        for(int j = 0; j < h; j++) {
            for(int k = 0; k < w; k++) {
                cin >> map[j][k];

                if(j == 0 || j == h - 1 || k == 0 || k == w - 1) {
                    if(map[j][k] != '*') {
                        startPos.emplace(j, k);
                    } 
                }
            }
        }
        status = 0;
        ans = 0;
        visitPos.clear();
        visitPos.resize(26);

        string basicKey;
        cin >> basicKey;

        if(basicKey[0] != '0') {
            for(int j = 0; j < basicKey.size(); j++) {
                status |= (1 << (basicKey[j] - 'a'));
            }
        }

        fill_n(visited[0], 10000, false);

        while(!startPos.empty()) {
            int y = startPos.front().first;
            int x = startPos.front().second;
            startPos.pop();

            if(visited[y][x]) continue;

            dfs(y, x);
        }
        cout << ans << endl;
    }
}