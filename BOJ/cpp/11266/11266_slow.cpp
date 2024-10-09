#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#define endl '\n'

vector<int> edges[10001];
vector<int> breakpoint;

void dfs(int v, int bp, bool* visited) {
    if(v == bp || visited[v]) return;

    visited[v] = true;
    for(int next : edges[v]) {
        dfs(next, bp, visited);
    }
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    int V, E;
    cin >> V >> E;

    int a, b, component, size;

    for(int i = 0; i < E; i++) {
        cin >> a >> b; 
        edges[a].emplace_back(b);
        edges[b].emplace_back(a);
    }
    
    for(int bp = 1; bp <= V; bp++) {        // 단절점 정하기 (단절점 : bp)
        if(edges[bp].size() <= 1) continue; // 간선이 한개 이하인 단절점은 건너뜀

        bool visited[10001] = {0};
        component = 0;

        for(int next : edges[bp]) {         // 간선 개수만큼 반복 (누적 V*E = 1,000,000,000)
            if(visited[next]) continue;
            
            dfs(next, bp, visited);
            component++;
        }
        if(component > 1) breakpoint.emplace_back(bp);
    }    
    sort(breakpoint.begin(), breakpoint.end());
    
    cout << breakpoint.size() << endl;
    for(int b : breakpoint) cout << b << ' ';
}