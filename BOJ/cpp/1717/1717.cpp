#include <iostream>
using namespace std;

int findParent(int* parent, int now) {
    if(parent[now] == now) return now;
    return parent[now] = findParent(parent, parent[now]);
}

void unionParent(int* parent, int a, int b) {
    a = findParent(parent, a);
    b = findParent(parent, b);
    if(a < b) parent[b] = a;
    else parent[a] = b;
}

bool checkParent(int* parent, int a, int b) {
    a = findParent(parent, a);
    b = findParent(parent, b);
    return a == b;
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, m;
    int parent[1000001];
    
    cin >> n >> m;
    for(int i = 0; i <= n; i++) parent[i] = i;

    for(int i = 0; i < m; i++) {
        int opt, a, b;
        cin >> opt >> a >> b;

        if(opt) cout << (checkParent(parent, a, b) ? "YES\n" : "NO\n");
        else unionParent(parent, a, b);
    }
}