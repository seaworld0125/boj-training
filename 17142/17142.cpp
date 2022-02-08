#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N, M, totalSpace = 0;
vector<pair<int, int>> virusPos;
int map[50][50];

int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

vector<int> sub_arr;

bool checkRange(const int & y, const int & x) {
    return (y >= N || x >= N || y < 0 || x < 0);
}

pair<int, bool> BFS() {
    queue<pair<int, int>> q;
    int infectSpace = 0;

    int tmp_map[50][50];
    fill_n(tmp_map[0], 2500, 0);
    
    for(int i = 0; i < sub_arr.size(); i++) {
        if(sub_arr[i]) {
            tmp_map[virusPos[i].first][virusPos[i].second] = -1;
            q.emplace(virusPos[i].first, virusPos[i].second);
        }
    }

    int maxTime = 0;

    while(!q.empty()) {
        auto pos = q.front();
        q.pop();

        int nowTime = (tmp_map[pos.first][pos.second] == -1 ? 0 : tmp_map[pos.first][pos.second]);

        for(int j = 0; j < 4; j++) {
            int y_ = pos.first + dy[j];
            int x_ = pos.second + dx[j];

            if(checkRange(y_, x_) || map[y_][x_] == 1 || tmp_map[y_][x_]) continue;

            if(map[y_][x_] == 0) { 
                maxTime = max(maxTime, nowTime + 1);
                infectSpace++;
            }
            tmp_map[y_][x_] = nowTime + 1;
            q.emplace(y_, x_);
        }
    }
    if(infectSpace != totalSpace) return {1e9, false};
    
    return {maxTime, true};
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N >> M;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> map[i][j];
            
            if(map[i][j] == 2) virusPos.emplace_back(i, j);
            if(!map[i][j]) totalSpace++;
        }
    }

    if(totalSpace == 0) {
        cout << 0;
        return 0;
    }

    for(int i = 0; i < virusPos.size() - M; i++) sub_arr.emplace_back(0);
    for(int i = virusPos.size() - M; i < virusPos.size(); i++) sub_arr.emplace_back(1);

    int ans = 1e9;
    bool flag = false;

    do
    {
        auto result = BFS();

        if(result.second) {
            ans = min(ans, result.first);
            flag = true;
        }

    } while (next_permutation(sub_arr.begin(), sub_arr.end()));

    if(flag) cout << ans;
    else cout << -1;
}