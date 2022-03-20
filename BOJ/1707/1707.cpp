#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void BFS(int start, vector<vector<int>> & edges, vector<int> & color) {
    int COLOR = false;

    queue<int> visit;
    visit.emplace(start);
    color[start] = COLOR;

    while(!visit.empty()) {
        int size = visit.size();

        COLOR = (COLOR ? false : true);
        for(int i = 0; i < size; i++) {
            int now = visit.front();
            visit.pop();

            for(int j = 0; j < edges[now].size(); j++) {
                if(color[edges[now][j]] != -1) continue;

                visit.emplace(edges[now][j]);
                color[edges[now][j]] = COLOR;
            }
        }
    }
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    int K, V, E;
    cin >> K;
    
    for(int i = 0; i < K; i++) {
        cin >> V >> E;

        vector<vector<int>> edges(V + 1);
        vector<int> color(V + 1, -1);

        for(int j = 0; j < E; j++) {
            int u, v;
            cin >> u >> v;

            edges[u].emplace_back(v);
            edges[v].emplace_back(u);
        }

        for(int j = 1; j <= V; j++) {
            if(color[j] == -1) {
                BFS(j, edges, color);
            }
        }

        bool flag = true;
        for(int j = 1; j <= V && flag; j++) {
            for(int k = 0; k < edges[j].size() && flag; k++) {
                if(color[j] == color[edges[j][k]]) {
                    flag = false;
                }
            }
        }
        if(flag) cout << "YES\n";
        else cout << "NO\n";
    }
}