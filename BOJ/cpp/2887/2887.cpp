#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

#define F first
#define S second

struct Sub {
    int sub;
    int a;
    int b;

    Sub(int s, int a, int b): sub(s), a(a), b(b) {}
};

int findParent(int* parent, int now) {
    if(parent[now] == now) return now;
    return findParent(parent, parent[now]);
}

bool checkParent(int* parent, int a, int b) {
    return findParent(parent, a) == findParent(parent, b);
}

void unionParent(int* parent, int a, int b) {
    a = findParent(parent, a);
    b = findParent(parent, b);

    if(a < b) parent[b] = a;
    else parent[a] = b;
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N;
    cin >> N;

    int parent[100000];
    for(int i = 0; i < N; i++) parent[i] = i;

    vector<Sub> subList;
    vector<pair<int, int>> X(N);
    vector<pair<int, int>> Y(N);
    vector<pair<int, int>> Z(N);

    for(int i = 0; i < N; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        
        X[i] = {x, i};
        Y[i] = {y, i};
        Z[i] = {z, i};
    }

    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
    sort(Z.begin(), Z.end());

    for(int i = 0; i < N - 1; i++) {
        subList.emplace_back(abs(X[i].F - X[i + 1].F), X[i].S, X[i + 1].S);
        subList.emplace_back(abs(Y[i].F - Y[i + 1].F), Y[i].S, Y[i + 1].S);
        subList.emplace_back(abs(Z[i].F - Z[i + 1].F), Z[i].S, Z[i + 1].S);
    }

    sort(subList.begin(), subList.end(), [](Sub & a, Sub & b){
        return a.sub < b.sub;
    });

    int ans = 0;
    for(Sub & sub : subList) {
        if(checkParent(parent, sub.a, sub.b)) continue;

        unionParent(parent, sub.a, sub.b);
        ans += sub.sub;
    }
    cout << ans;
}