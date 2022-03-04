#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int findParent(int* parent, int now) {
    if(parent[now] == now) return now;
    return parent[now] = findParent(parent, parent[now]);
}

void unionParent(int* parent, int a, int b) {
    a = findParent(parent, a);
    b = findParent(parent, b);
    if(a > b) parent[parent[a]] = b;
    else parent[parent[b]] = a; 
}

bool checkParent(int* parent, int a, int b) {
    return findParent(parent, a) == findParent(parent, b);
}

struct Edge {
    int start;
    int end;
    int cost;

    Edge(int s, int e, int c) : start(s), end(e), cost(c) {}
};

int main() {
    // 노드 개수
    const int nodes = 6;

    // 간선 정보를 입력받는다
    vector<Edge> edges;
    edges.emplace_back(5, 6, 5);
    edges.emplace_back(3, 5, 3);
    edges.emplace_back(2, 4, 3);
    edges.emplace_back(1, 2, 3);
    edges.emplace_back(4, 3, 2);
    edges.emplace_back(4, 6, 1);
    edges.emplace_back(1, 3, 1);

    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        if(a.cost < b.cost) return true;
        else if(a.cost == b.cost) {
            return a.start > b.start;
        }
        return false;
    });

    int parent[nodes];
    for(int i = 0; i < nodes; i++) parent[i] = i;

    int sum = 0;
    for(int i = 0; i < edges.size(); i++) {
        if(!checkParent(parent, edges[i].start - 1, edges[i].end - 1)) {
            cout << "select >> " << edges[i].start << ", " << edges[i].end << ", " << edges[i].cost << endl;
            sum += edges[i].cost;
            unionParent(parent, edges[i].start - 1, edges[i].end - 1);
        }
    }

    cout << "sum : " << sum << endl; 
}