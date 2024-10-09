#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define INF (int)1e9
#define COST_MAX 10001

int T, N, M, K;

// dist[도착지][비용] = 시간
int dist[101][COST_MAX]; 

/*
    우선순위  : 가장 빨리 갈 수 있는 경로        
    제한 조건 : M원 이하로 갈 수 있는 경로
*/

struct Info {
    int dest;
    int cost;
    int time;

    Info(int d, int c, int t): dest(d), cost(c), time(t) {}
};

struct compare {
    bool operator()(Info& a, Info& b) {
        return a.cost > b.cost;
    } 
};

vector<Info> edges[101];

inline void clearV() {
    for(int i = 0; i <= N; i++) {
        for(int j = 0; j <= M; j++) {
            dist[i][j] = INF;
        }
        edges[i].clear();
    }
}

void dijkstra() {
    priority_queue<Info, vector<Info>, compare> pq; // Info의 cost를 오름차순 정렬
    pq.emplace(1, 0, 0); 
    dist[1][0] = 0; // dist[1에서][0비용으로] = 0초가 걸림

    while(!pq.empty()) {
        int now = pq.top().dest;
        int d = pq.top().cost;
        int t = pq.top().time;
        pq.pop();

        if(dist[now][d] < t) continue;

        int size = edges[now].size();
        for(int i = 0; i < size; i++) {
            int cost = d + edges[now][i].cost;
            int time = t + edges[now][i].time;

            if(cost > M) continue;

            if(dist[edges[now][i].dest][cost] > time) { // 해당 비용으로 도달할 수 있는 최단 시간으로 갱신
                dist[edges[now][i].dest][cost] = time;
                pq.emplace(edges[now][i].dest, cost, time);
            }
        }
    }
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> T;

    for(int i = 0; i < T; i++) {
        cin >> N >> M >> K;

        clearV();

        int u, v, c, d;
        for(int j = 0; j < K; j++) {
            cin >> u >> v >> c >> d;

            edges[u].emplace_back(v, c, d); // 단방향 // 비용, 도착지, 시간
        }

        dijkstra();

        int ans = INF;
        for(int j = 1; j <= M; j++) {
            ans = min(ans, dist[N][j]); // M이하의 모든 비용의 경우에서 가장 짧은 시간으로 갱신
        }
        if(ans == INF) cout << "Poor KCM\n";
        else cout << ans << '\n';
    }
}