#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
    
#define pii pair<int, int>
#define F first 
#define S second

int N;
int fatigue[51][51];
char map[51][51];
bool visited[51][51];

int py, px;
vector<pii> houses;

int dy[] = {1, -1, 0, 0, -1, 1, 1, -1};
int dx[] = {0, 0, 1, -1, 1, 1, -1, -1};

bool BFS(const int& MIN, const int& MAX) {

    memset(visited, 1, sizeof(visited));

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {

            if(MIN <= fatigue[i][j] && fatigue[i][j] <= MAX) {
                visited[i][j] = false;
            }
        }
    }

    if(visited[py][px]) return false;

    for(auto pos : houses) {
        // 하나라도 true라면 현재 MIN, MAX로 모든 집을 방문할 수 없다는 뜻
        if(visited[pos.F][pos.S]) return false;
    }

    queue<pii> visit;
    visit.emplace(py, px);
    visited[py][px] = true;

    while(!visit.empty()) {

        auto pos = visit.front();
        visit.pop();

        for(int i = 0; i < 8; i++) {

            int y = pos.F + dy[i];
            int x = pos.S + dx[i];

            if(y < 0 || x < 0 || y >= N || x >= N || visited[y][x]) continue;

            visit.emplace(y, x);
            visited[y][x] = true;
        }
    }    

    // 탐색이 끝나고 하나라도 방문하지 못한 집이 있다면 return false;
    for(auto pos : houses) {
        if(!visited[pos.F][pos.S]) return false;
    }
    return true;
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> N;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> map[i][j];

            if(map[i][j] == 'P') {
                py = i;
                px = j;
            }
            else if(map[i][j] == 'K') {
                houses.emplace_back(i, j);
            }
        }
    }

    set<int> bucket;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> fatigue[i][j];
            bucket.emplace(fatigue[i][j]);
        }
    }

    vector<int> range;
    range.assign(bucket.begin(), bucket.end());

    int LOW = 0, 
        HIGH = 0,
        ANS = 999999;

    int size = range.size();

    while(LOW < size) {

        if(BFS(range[LOW], range[HIGH])) {
            ANS = min(ANS, range[HIGH] - range[LOW]);
            // printf("range[HIGH] = %d, range[LOW] = %d\n", range[HIGH], range[LOW]);
            LOW++;
        }
        else if(HIGH < size) {
            HIGH++;
        }
        else {
            break;
        }
    }
    cout << ANS;
}