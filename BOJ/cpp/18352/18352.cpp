#include <iostream>
#include <queue>
using namespace std;

int N, M, K, X; // 도시, 도로, edge, start

vector<int> edges[1000001];
int dp[300001];

void dijkstra(int start) {

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, start);

    fill_n(dp, N + 1, (int)1e9);
    dp[start] = 0;

    while(!pq.empty()) {
        int cost = pq.top().first;
        int now = pq.top().second;
        pq.pop();

        if(dp[now] < cost) continue;

        for(int i = 0; i < edges[now].size(); i++) {
            int dist = cost + 1;
            if(dist < dp[edges[now][i]]) {
                dp[edges[now][i]] = dist;
                pq.emplace(dist, edges[now][i]);
            }
        }
    }
}

int main() {

    cin >> N >> M >> K >> X;

    int a, b;
    for(int i = 0; i < M; i++) {
        cin >> a >> b;
        edges[a].emplace_back(b);
    }

    priority_queue<int, vector<int>, greater<int>> q;
    for(int i = 1; i < N; i++) {
        if(dp[i] == K) {
            q.emplace(dp[i]);
        }
    }

    if(q.size()) {
        int size = q.size();
        for(int i = 0; i < size; i++) {
            cout << q.top() << ' ';
            q.pop();
        }
    }
    else cout << -1;
}