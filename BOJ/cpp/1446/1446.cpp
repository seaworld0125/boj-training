#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, D; // D = target
int dist[10001];
vector<pair<int, int>> edges[10001];

void dijkstra() {
    fill_n(dist, D + 1, (int)1e9);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, 0);
    dist[0] = 0;

    while(!pq.empty()) {
        int curDist = pq.top().first;
        int now = pq.top().second;
        pq.pop();

        if(dist[now] < curDist) continue;

        for(int i = 0; i < edges[now].size(); i++) {
            int cost = edges[now][i].first + curDist;

            if(cost < dist[edges[now][i].second]) {
                dist[edges[now][i].second] = cost;
                pq.emplace(cost, edges[now][i].second);
            }
        }
    }       
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> N >> D;

    int a, b, d;

    bool vertex[10001] = {0};
    vertex[0] = true;

    for(int i = 0; i < N; i++) {
        cin >> a >> b >> d;
        edges[a].emplace_back(d, b); // 거리, 목적지

        vertex[a] = true;
        vertex[b] = true;
    }

    for(int i = 0; i <= D; i++) {
        if(vertex[i]) {
            for(int j = i + 1; j <= D; j++) {
                if(vertex[j]) {
                    edges[i].emplace_back(j - i, j);
                }
            }
        }
    }

    dijkstra();

    int ans = D;
    for(int i = 1; i <= D; i++) {
        ans = min(ans, D - i + dist[i]);
    }
    cout << ans;
}