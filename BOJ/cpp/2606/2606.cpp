#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, E;
vector<int> edges[101];

void BFS() {
    int ans = 0;

    bool visited[101];
    fill_n(visited, 101, false);
    visited[1] = true;

    queue<int> visit;
    visit.emplace(1);

    while(!visit.empty()) {
        int now = visit.front();
        visit.pop();

        for(int i = 0; i < edges[now].size(); i++) {
            if(visited[edges[now][i]]) continue;

            ans++;
            visit.emplace(edges[now][i]);
            visited[edges[now][i]] = true;
        }
    }
    cout << ans;
}

int main() {ios_base::sync_with_stdio(false); cin.tie();
    cin >> N >> E;

    int a, b;
    for(int i = 0; i < E; i++) {
        cin >> a >> b;
        edges[a].emplace_back(b);
        edges[b].emplace_back(a);
    }
    BFS();
}