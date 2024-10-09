#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define F first
#define S second
#define INF (int)1e9

int N, E;
vector<pair<int, int>> edges[801]; // dist, vertex

int dp[801];

void dijkstra(int start) {
    priority_queue<pair<int, int>> pq;
    pq.emplace(0, start);

    fill_n(dp, N + 1, INF);
    dp[start] = 0;

    int dist, now, cost;
    while(!pq.empty()) {
        dist = -pq.top().F;
        now = pq.top().S;
        pq.pop();

        if(dp[now] < dist) continue;

        for(int i = 0; i < edges[now].size(); i++) {
            cost = edges[now][i].F + dist;
            if(cost < dp[edges[now][i].S]) {
                dp[edges[now][i].S] = cost;
                pq.emplace(-cost, edges[now][i].S);
            }
        }
    }
}

void cant() {
    cout << -1;
}
#define FAIL {cant(); return 0;}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> N >> E;

    if(!E) {
        cout << -1;
        return 0;
    }

    int a, b, c;
    for(int i = 0; i < E; i++) {
        cin >> a >> b >> c;
        edges[a].emplace_back(c, b);
        edges[b].emplace_back(c, a);
    }
    int v1, v2;
    cin >> v1 >> v2;

    int ans1 = 0, ans2 = 0;

    dijkstra(1);
    ans1 += dp[v1]; // 1 - v1 - v2 - N
    ans2 += dp[v2]; // 1 - v2 - v1 - N
    if(ans1 >= INF && ans2 >= INF) FAIL

    dijkstra(v1);
    ans1 += dp[v2];
    ans2 += dp[v2];
    ans2 += dp[N];
    if(ans1 >= INF && ans2 >= INF) FAIL

    dijkstra(v2);
    ans1 += dp[N];

    int ans = min(ans1, ans2);

    cout << (ans >= INF ? -1 : ans);
}