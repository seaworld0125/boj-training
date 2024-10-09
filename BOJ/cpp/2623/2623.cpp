#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M, m, a, b;
int inDegree[1001] = {0};
vector<int> edges[1001];

void topologySort() {
    vector<int> result(N);
    queue<int> vq;

    for(int i = 1; i <= N; i++)
        if(inDegree[i] == 0)
            vq.emplace(i);

    for(int i = 0; i < N; i++) {
        if(vq.empty()) {
            cout << 0;
            return;
        }
        
        int now = vq.front();
        vq.pop();
        result[i] = now;

        for(int j = 0; j < edges[now].size(); j++) {
            int node = edges[now][j];

            if(inDegree[node] > 0) {
                if(--inDegree[node] == 0) {
                    vq.emplace(node);
                }
            }
        }
    }
    for(int node : result)
        cout << node << '\n';
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;

    for(int i = 0; i < M; i++) {
        cin >> m;

        vector<int> order(m);
        for(int j = 0; j < m; j++)
            cin >> order[j];

        for(int j = 0; j < m - 1; j++) {
            edges[order[j]].emplace_back(order[j + 1]);
            inDegree[order[j + 1]]++;
        }
    }
    topologySort();
}