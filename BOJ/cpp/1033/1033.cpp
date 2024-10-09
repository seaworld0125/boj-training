#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// #define ll long long

bool visited[11];
int ans[11];
vector<int> edges[11];

int getGcd(int a, int b) {
    int r;
    
    if(a < b) {
        r = a;
        a = b;
        b = r;
    }

    while(b != 0) {
        r = a % b;
        a = b; 
        b = r;
    }
    return a;
}

void update(int now, const int& val) {
    visited[now] = true;
    ans[now] *= val;

    for(int next : edges[now]) {
        if(visited[next]) continue;

        update(next, val);
    }
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    int N;
    cin >> N;

    int a, b, p, q;

    fill_n(ans, N, 1);

    for(int i = 0; i < N - 1; i++) {
        cin >> a >> b >> p >> q;

        int gcd = getGcd(ans[a], ans[b]);
        int x = q * ans[a] / gcd;
        int y = p * ans[b] / gcd;

        gcd = getGcd(x, y);
        memset(visited, 0, sizeof(visited));

        update(b, x / gcd);
        update(a, y / gcd);

        edges[a].emplace_back(b);
        edges[b].emplace_back(a);
    }

    for(int i = 0; i < N; i++) { 
        cout << ans[i] << ' ';
    }
}