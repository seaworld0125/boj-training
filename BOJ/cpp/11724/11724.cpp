#include <iostream>
using namespace std;

int findParent(int* parent, int now) {
    if(parent[now] == now) return now;
    return parent[now] = findParent(parent, parent[now]);
}

bool unionParent(int* parent, int a, int b) {
    a = findParent(parent, a);
    b = findParent(parent, b);
    if(a < b) parent[b] = a;
    else parent[a] = b;
    return a != b;  
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    int N, M;
    cin >> N >> M;

    int parent[1001];
    for(int i = 1; i <= N; i++) parent[i] = i;

    int ans = N;
    for(int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;

        ans -= unionParent(parent, a, b);
    }
    cout << ans;
}