#include <iostream>
#include <queue>
using namespace std;

#define INF (int)1e9
#define F first
#define S second

int N, M, K;
int map[1001][1001];
int dp[1001][1001];

int dy[] = {1, 0, -1, 0};
int dx[] = {0, 1, 0, -1};

inline bool checkRange(int y, int x) {
    return y < 0 || x < 0 || y >= N || x >= M;
}

int BFS() {
    queue<pair<int, int>> q;
    q.emplace(0, 0);
    dp[0][0] = 0;

    int ans = INF;
    int dist = 1;
    while(!q.empty()) {

        int size = q.size();
        for(int i = 0; i < size; i++) {

            auto pos = q.front();
            q.pop();
            if(pos.F == N - 1 && pos.S == M - 1) {
                ans = (ans <= dist ? ans : dist);
                continue;
            }

            for(int j = 0; j < 4; j++) {
                int y = pos.F + dy[j];
                int x = pos.S + dx[j];

                int cost = dp[pos.F][pos.S] + map[y][x];
                if(checkRange(y, x) || dp[y][x] <= cost || K < cost) continue;
                
                dp[y][x] = cost;
                q.emplace(y, x);
            }
        }   
        dist++;     
    }
    return ans;
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M >> K;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            char num;
            cin >> num;
            map[i][j] = num - '0';
            dp[i][j] = INF;
        }
    }

    int ans = BFS();
    if(dp[N - 1][M - 1] > K) cout << -1;
    else cout << ans;
}