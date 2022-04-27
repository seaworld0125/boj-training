#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define piii pair<int, pair<int, int>>
#define cost first
#define v1 second.first
#define v2 second.second

int parent[110000];
vector<piii> edges;

int findParent(int now) {
    if(parent[now] == now) return now;
    return parent[now] = findParent(parent[now]);
}

bool unionParent(int a, int b) {
    a = findParent(a);
    b = findParent(b);

    if(a == b) return false;

    if(a < b) parent[b] = a;
    else parent[a] = b;

    return true;
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    int N, M, A, B, C;

    cin >> N >> M;

    for(int i = 0; i <= N; i++) parent[i] = i;

    for(int i = 0; i < M; i++) {
        cin >> A >> B >> C; 

        edges.push_back({C, {A, B}});
    }

    sort(edges.begin(), edges.end(), [](piii& a, piii& b) {
        if(a.cost < b.cost) return true;
        return false;
    });

    int size = edges.size(), 
        maxCost = 0, 
        ans = 0;

    for(int i = 0; i < size; i++) {
        if(unionParent(edges[i].v1, edges[i].v2)) {
            ans += edges[i].cost;
            maxCost = max(maxCost, edges[i].cost);
        }
    }
    cout << ans - maxCost;
}