#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int vertex1;
    int vertex2;
    int cost;

    Edge(int a, int b, int c) : vertex1(a), vertex2(b), cost(c) {}
};

int findParent(int* parent, int now) {
    if(parent[now] == now) return now;
    else return findParent(parent, parent[now]);
}

void unionParent(int* parent, int a, int b) {
    a = findParent(parent, a);
    b = findParent(parent, b);
    if(a > b) parent[a] = b;
    else parent[b] = a;
}

bool checkParent(int* parent, int a, int b) {
    return findParent(parent, a) == findParent(parent, b);
}

int N, M, START, END;
int parent[10001];
vector<Edge> edges;

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;

    for(int i = 1; i <= N; i++) parent[i] = i;

    for(int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        edges.emplace_back(a, b, c);
    }
    cin >> START >> END;

    sort(edges.begin(), edges.end(), [](Edge & a, Edge & b) {
        if(a.cost > b.cost) return true;
        else return false;
    });

    int ans = (int)1e9;
    for(Edge & edge : edges) {
        if(checkParent(parent, edge.vertex1, edge.vertex2)) continue;

        unionParent(parent, edge.vertex1, edge.vertex2);

        ans = min(ans, edge.cost);

        if(checkParent(parent, START, END)) {
            cout << ans;
            break;
        }
    }
}