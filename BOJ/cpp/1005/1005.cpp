#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int T, N, K;
int a, b;
int target;

void topologySort(int target, vector<int> * edges, vector<int> & inDegree, vector<int> & cost) {
    vector<int> order;
    vector<int> dp(N + 1, 0);

    queue<int> vq;
    for(int i = 1; i <= N; i++) {
        if(inDegree[i] == 0) {
            vq.emplace(i);
            dp[i] = cost[i];
        }
    }

    for(int i = 0; i < N; i++) {
        int now = vq.front();
        vq.pop();

        if(now == target) break;
        order.emplace_back(now);

        for(int j = 0; j < edges[now].size(); j++) {
            if(--inDegree[edges[now][j]] == 0) {
                vq.emplace(edges[now][j]);
            }
        }
    }
    for(int i = 0; i < order.size(); i++) {
        for(int j = 0; j < edges[order[i]].size(); j++) {
            dp[edges[order[i]][j]] = max(dp[edges[order[i]][j]], dp[order[i]] + cost[edges[order[i]][j]]);
        }
    }
    cout << dp[target] << endl;
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> T;

    for(int i = 0; i < T; i++) {
        cin >> N >> K;

        vector<int> cost(N + 1);
        for(int j = 1; j <= N; j++) cin >> cost[j];

        vector<int> edges[1001];
        vector<int> inDegree(N + 1, 0);

        for(int j = 0; j < K; j++) {
            cin >> a >> b;
            edges[a].emplace_back(b);

            inDegree[b]++;
        }
        cin >> target;
        topologySort(target, edges, inDegree, cost);
    }
}