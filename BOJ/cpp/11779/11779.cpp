#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define F first
#define S second
#define ll long long

// dest, cost
vector<pair<int, ll>> busLine[1001];
int n, m, startCity, destCity;

ll dist[1001];
vector<int> path[1001];

void dijkstra() {
    // -cost, vertex
    priority_queue<pair<ll, int>> pq;
    pq.emplace(0, startCity);
    dist[startCity] = 0;

    while(!pq.empty()) {
        ll c = -pq.top().F;
        int v = pq.top().S;
        pq.pop();

        if(dist[v] < c) continue;

        for(int i = 0; i < busLine[v].size(); i++) {
            int dest = busLine[v][i].F;
            ll cost = c + busLine[v][i].S;

            if(cost < dist[dest]) {
                // dist를 갱신해주는 작업
                dist[dest] = cost;
                pq.emplace(-cost, dest);
                // path를 갱신해주는 작업
                path[dest].clear();
                path[dest].assign(path[v].begin(), path[v].end());
                path[dest].emplace_back(v);
            }
        }
    }
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;

    int start, dest, cost;
    for(int i = 0; i < m; i++) {
        cin >> start >> dest >> cost;

        // 구간은 단방향이다.
        busLine[start].emplace_back(dest, cost);
    }

    cin >> startCity >> destCity;

    fill_n(dist, 1001, (ll)1e9);
    dijkstra();

    cout << dist[destCity] << endl;
    cout << path[destCity].size() + 1 << endl;
    for(int city : path[destCity]) {
        cout << city << ' ';
    }
    cout << destCity;
}