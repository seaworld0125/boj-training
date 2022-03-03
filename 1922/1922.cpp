#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int start;
    int end;
    int cost;

    Edge(int s, int e, int c):start(s), end(e), cost(c) {}

    bool operator<(Edge & edge) {
        return this->cost < edge.cost;
    }
};

int findParent(int* parent, int now) {
    if(parent[now] == now) return now;
    return findParent(parent, parent[now]);
}

void unionParent(int* parent, int a, int b) {
    a = findParent(parent, a);
    b = findParent(parent, b);
    if(a < b) parent[b] = a;
    else parent[a] = b;
}

bool checkParent(int* parent, int a, int b) {
    return findParent(parent, a) == findParent(parent, b);
}

int N, M;
vector<Edge> edges;
int parent[1001];

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;

    for(int i = 0; i <= N; i++) parent[i] = i;

    for(int i = 0; i < M; i++) {
        int start, end, cost;
        cin >> start >> end >> cost;
        edges.emplace_back(start, end, cost);
    }
    sort(edges.begin(), edges.end());

    int minimumCost = 0;
    for(int i = 0; i < M; i++) {
        if(!checkParent(parent, edges[i].start, edges[i].end)) {
            unionParent(parent, edges[i].start, edges[i].end);

            minimumCost += edges[i].cost;
        }
    }
    cout << minimumCost;
}