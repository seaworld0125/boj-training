#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int goal;
    int cost;
    Edge(int g, int c) : goal(g), cost(c) {}
};

int FAR,
    MAX = 0;
vector<Edge> edges[100001];
bool visited[100001] = {0};

void dfs(int now, int dist) {
    if(dist > MAX) {
        FAR = now;
        MAX = dist;
    }
    visited[now] = true;

    for(Edge & next : edges[now]) {
        if(visited[next.goal]) continue;

        dfs(next.goal, dist + next.cost);
    }
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    int V;
    cin >> V;

    int start, goal, cost;
    for(int i = 1; i <= V; i++) {
        
        cin >> start;
        while(1) {
            cin >> goal;
            if(goal == -1) break;

            cin >> cost;
            edges[start].emplace_back(goal, cost);
            edges[goal].emplace_back(start, cost);
        }
    }

    dfs(1, 0);

    fill_n(visited, V + 1, false);
    MAX = 0;
    dfs(FAR, 0);

    cout << MAX;
}