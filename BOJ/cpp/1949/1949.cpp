#include <iostream>
#include <vector>
using namespace std;

int N;
int residents[10001];
bool visited[10001];

vector<int> edges[10001];
int dp[10001][2];

void recursive(int now) {
    visited[now] = true;

    for(int next : edges[now])
        if(!visited[next]) recursive(next);

    dp[now][0] = 0;
    dp[now][1] = residents[now];

    for(int next : edges[now]) {
        dp[now][0] += max(dp[next][0], dp[next][1]);
        dp[now][1] += dp[next][0];
    } 
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> residents[i];

    for(int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;

        edges[a].emplace_back(b);
        edges[b].emplace_back(a);
    }

    fill_n(visited, 10001, false);
    fill_n(dp[0], 20002, 0);

    recursive(1);
    cout << max(dp[1][1], dp[1][0]);
}