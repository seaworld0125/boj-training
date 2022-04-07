#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

#define pii pair<int, int>
#define INF (int)1e9
#define F first
#define S second

int N, M;
char map[110][110];
int dist[110][110][3];

int dy[] = {1, -1, 0, 0};
int dx[] = {0, 0, -1, 1};

void BFS(pii startPos, int idx) {
    deque<pii> visit;
    visit.push_front(startPos);
    dist[startPos.F][startPos.S][idx] = 0;

	int ans = (int)1e9;

    while(!visit.empty()) {
        int y = visit.front().F;
        int x = visit.front().S;
        visit.pop_front();

        for(int i = 0; i < 4; i++) {
            int y_ = y + dy[i];
            int x_ = x + dx[i];

            if(y_ < 0 || x_ < 0 || y_ >= N + 2 || x_ >= M + 2 || map[y_][x_] == '*') continue;

            int cost = 0;
            if(map[y_][x_] == '#') cost = 1;

            if(dist[y][x][idx] + cost < dist[y_][x_][idx]) {
                dist[y_][x_][idx] = dist[y][x][idx] + cost;

                if(cost) visit.emplace_back(y_, x_);
                else visit.emplace_front(y_, x_);
            }
        }
    }
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
	int T;
    cin >> T;

	while(T--) {
    	cin >> N >> M;

		vector<pii> start;

	    for(int i = 0; i <= N + 1; i++) {
    	    for(int j = 0; j <= M + 1; j++) {
        	    if(i == 0 || j == 0 || i == N + 1 || j == M + 1) map[i][j] = '.';
        	    else cin >> map[i][j];

        	    if(map[i][j] == '$') start.emplace_back(i, j);
        	}
    	}

   		start.emplace_back(0, 0);

		fill_n(dist[0][0], (110 * 110 * 3), INF);
    	for(int i = 0; i < 3; i++) {
        	BFS(start[i], i);
    	}

		long long ans = INF;
        for(int j = 0; j <= N + 1; j++) {
            for(int k = 0; k <= M + 1; k++) {
                if(map[j][k] == '*') continue;

				long long tmp = (map[j][k] == '#' ? -2 : 0);
                for(int i = 0; i < 3; i++) {
					tmp += dist[j][k][i];
                }
                ans = min(ans, tmp);  
            }
	    }
		cout << ans << endl;
    }
}