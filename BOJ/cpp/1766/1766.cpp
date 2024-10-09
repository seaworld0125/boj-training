#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define INF (int)1e9

int N, M;
int inDegree[32001] = {0};
vector<int> edges[32001];

void topologySort() {
    priority_queue<int, vector<int>, greater<int>> nodes;
    for(int i = 1; i <= N; i++) {
        if(inDegree[i] == 0) {
            nodes.emplace(i);
        }
    }
    while(!nodes.empty()) {
        int now = nodes.top();
        nodes.pop();

        cout << now << ' ';

        for(int i = 0; i < edges[now].size(); i++) {
            if(--inDegree[edges[now][i]] == 0) {
                nodes.emplace(edges[now][i]);
            }
        }
    }
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> N >> M;

    int a, b;
    for(int i = 0; i < M; i++) {
        cin >> a >> b;
        edges[a].emplace_back(b);

        inDegree[b]++; 
    }
    topologySort();
}