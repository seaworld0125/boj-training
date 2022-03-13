#include <iostream>
#include <vector>
using namespace std;

int N;
int dp[1000001][2];
bool visited[1000001];
vector<int> edges[1000001];

void solve(int now) {
    visited[now] = true;

    for(int next : edges[now])
        if(!visited[next]) solve(next);

    dp[now][0] = 0;
    dp[now][1] = 1;

    for(int next : edges[now]) {
        dp[now][0] += dp[next][1];
        dp[now][1] += min(dp[next][0], dp[next][1]);
    }
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;

        edges[a].emplace_back(b);
        edges[b].emplace_back(a);
    }

    fill_n(dp[0], 2000002, 0);
    fill_n(visited, N + 1, false);

    solve(1);
    cout << min(dp[1][0], dp[1][1]);
}