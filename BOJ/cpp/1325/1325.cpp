#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

#define INF (int)1e9

int N, M;
vector<int> graph[10001];

int MAX_CNT = 0;
int rec[10001];
bool visited[10001];

int dfs(int now) {

    int cnt = 1;
    visited[now] = true;
    
    for(auto next : graph[now]) {
        if(visited[next]) continue;
        cnt += dfs(next);
    }
    return cnt;
}

int main() {

    cin >> N >> M;

    for(int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        graph[b].push_back(a); // 관계 역전
    }

    for(int i = 1; i <= N; i++) {
        memset(visited, 0, sizeof(visited));
        rec[i] = dfs(i);
        MAX_CNT = max(MAX_CNT, rec[i]); 
    }

    vector<int> ans;

    for(int i = 1; i <= N; i++) {
        if(MAX_CNT == rec[i]) {
            ans.push_back(i);
        }
    }

    sort(ans.begin(), ans.end());

    for(auto i : ans) {
        printf("%d ", i);
    }
}