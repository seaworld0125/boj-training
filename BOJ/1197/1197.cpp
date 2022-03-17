#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int V, E;
int A, B, C;

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

struct Edge {
    int a;
    int b;
    int c;

    Edge(int a, int b, int c) : a(a), b(b), c(c) {}
};

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> V >> E;

    vector<Edge> edges;
    int parent[10001];

    for(int i = 0; i <= V; i++) parent[i] = i;

    for(int i = 0; i < E; i++) {
        cin >> A >> B >> C;
        edges.emplace_back(A, B, C);
    }

    sort(edges.begin(), edges.end(), [](Edge &a, Edge &b) {
        return a.c < b.c;
    });
    
    int ans = 0;
    int a, b, c;
    for(int i = 0; i < E; i++) {
        a = edges[i].a;
        b = edges[i].b;
        c = edges[i].c;

        if(checkParent(parent, a, b)) continue;

        ans += c;
        unionParent(parent, a, b);
    }
    cout << ans;
}