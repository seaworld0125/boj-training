#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m, a, b;
int start, goal, ans = -1;

vector<int> child[101];
bool visited[101] = {0};

void BFS() {
    queue<int> visit;
    visit.emplace(start);
    visited[start] = true;

    int size, cur, now, dist = -1;

    while(!visit.empty()) {
        dist++;
        size = visit.size();
        for(int i = 0; i < size; i++) {
            cur = visit.front();
            visit.pop();

            if(cur == goal) {
                ans = dist;
                return;
            }
            for(int j = 0; j < child[cur].size(); j++) {
                now = child[cur][j];
                if(visited[now]) continue;

                visited[now] = true;
                visit.emplace(now);
            }
        }
    }
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> n;
    cin >> start >> goal;
    cin >> m;

    for(int i = 0; i < m; i++) {
        cin >> a >> b; 
        child[a].emplace_back(b);
        child[b].emplace_back(a);
    }
    BFS();
    cout << ans;
}