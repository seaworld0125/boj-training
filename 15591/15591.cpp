// Union find를 이용해서 다시 풀어보기

#include <iostream>
#include <vector>
#include <stack>
using namespace std; 

#define F first
#define S second
#define ll long long
#define INF (ll)1e9

int N, Q;

// vertex, dist
vector<pair<int, ll>> graph[5001];
ll dist[5001];
bool visited[5001]; 

void DFS(stack<int> & visit, int start) {
    int now = visit.top();
    
    for(int i = 0; i < graph[now].size(); i++) {
        int vertex = graph[now][i].first;
        
        if(!visited[vertex]) {
            visit.emplace(vertex);
            visited[vertex] = true;

            if(dist[now] > graph[now][i].S || dist[vertex] > graph[now][i].S) {
                dist[vertex] = graph[now][i].S;
            }
            if(now != start && dist[now] < dist[vertex]){
                dist[vertex] = dist[now];
            }

            if(dist[vertex])
            
            DFS(visit, start);
        }
    }
    visit.pop();
}

int main() {
    cin >> N >> Q;

    int p, q;
    ll r;
    for(int i = 0; i < N - 1; i++) {
        cin >> p >> q >> r;

        graph[p].emplace_back(q, r);
        graph[q].emplace_back(p, r);
    }

    ll k;
    int v, prev = 0;
    for(int i = 0; i < Q; i++) {
        cin >> k >> v;

        if(prev != v) {
            prev = v;
            
            fill_n(visited, N + 1, false);
            fill_n(dist, N + 1, INF);
            dist[v] = 0;
            
            stack<int> visit;
            visit.emplace(v);

            DFS(visit, v);
        }

        int ans = 0;

        for(int j = 1; j <= N; j++)
            if(k <= dist[j] && dist[j] != INF) ans++;

        cout << ans << endl;
    }
}