#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<vector<int>> edges(1001);
int N, M, V;
bool visited[1001];

void DFS(int now) {
    visited[now] = true;
    cout << now << ' ';

    for(int i = 0; i < edges[now].size(); i++) {
        if(visited[edges[now][i]]) continue;
        DFS(edges[now][i]);
    }
}

void BFS(int start) {
    fill_n(visited, N + 1, false);
    visited[start] = true;
    
    queue<int> visit;
    visit.emplace(start);

    while(!visit.empty()) {
        int v = visit.front();
        visit.pop();
        cout << v << ' ';

        for(int i = 0; i < edges[v].size(); i++) {
            if(visited[edges[v][i]]) continue;
            visit.emplace(edges[v][i]);
            visited[edges[v][i]] = true;
        }
    }
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M >> V;
    fill_n(visited, N + 1, false);

    int start, end;
    for(int i = 0; i < M; i++) {
        cin >> start >> end;
        edges[start].emplace_back(end);
        edges[end].emplace_back(start);
    }
    for(int i = 1; i <= N; i++)
        sort(edges[i].begin(), edges[i].end());

    DFS(V); 
    cout << '\n';
    BFS(V);   
}