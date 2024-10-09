#include <iostream>
#include <set>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

#define pii pair<int, int>
#define F first
#define S second

int n;
int map[201][201];
bool visited[201][201];

set<int> bucket;
vector<int> range;

int dy[] = {1, -1, 0, 0};
int dx[] = {0, 0, 1, -1};

bool BFS(const int& MIN, const int& MAX) {

    memset(visited, 1, sizeof(visited));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {

            if(MIN <= map[i][j] && map[i][j] <= MAX) {

                visited[i][j] = false;
            }
        }
    }

    // 이 MIN, MAX로는 탐색을 시작할 수 없다는 의미
    if(visited[0][0]) return false;

    queue<pii> visit;
    visited[0][0] = true;
    visit.emplace(0, 0);

    while(!visit.empty()) {

        auto pos = visit.front();
        visit.pop();

        // 목적지에 도착했다면
        if(pos.F == n - 1 && pos.S == n - 1) {
            return true;
        }

        for(int i = 0; i < 4; i++) {

            int y = pos.F + dy[i];
            int x = pos.S + dx[i];

            if(y < 0 || x < 0 || y >= n || x >= n || visited[y][x]) {
                continue;
            }

            visited[y][x] = true;
            visit.emplace(y, x);
        }
    }
    return false;
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> map[i][j];
            bucket.emplace(map[i][j]);
        }
    }

    // 정렬하고 중복이 제거된 채로 range에 재할당
    range.assign(bucket.begin(), bucket.end());

    // LOW, MAX 모두 Range 배열의 0번 index(가장 작은 수)로 초기화
    int LOW = 0, 
        HIGH = 0, 
        ANS = 200;

    int size = range.size();

    while(LOW < size) {

        // 잘 도착했다면
        if(BFS(range[LOW], range[HIGH])) {
            ANS = min(ANS, range[HIGH] - range[LOW]);
            // printf("range[LOW] = %d, range[HIGH] = %d\n", range[LOW], range[HIGH]);
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