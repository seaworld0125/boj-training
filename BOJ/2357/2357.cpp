#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define pii pair<int, int>
#define MAX first
#define MIN second

pii tree[300000];
int arr[100001];

int size;

pii build(int node, int left, int right) {
    if(left == right) {
        tree[node] = {arr[left], arr[left]};
        return tree[node];
    }
    pii lVal = build(node * 2, left, (left + right) / 2);
    pii rVal = build(node * 2 + 1, ((left + right) / 2) + 1, right);

    return tree[node] = {max(lVal.MAX, rVal.MAX), min(lVal.MIN, rVal.MIN)};
}

void rangeQuery(const int& qLeft, const int& qRight, pii& ans, int node, int left, int right) {
    if(qRight < left || right < qLeft) {
        return;
    }
    
    if(qLeft <= left && right <= qRight) {
        ans.MAX = max(ans.MAX, tree[node].MAX);
        ans.MIN = min(ans.MIN, tree[node].MIN);
        return;
    }
    rangeQuery(qLeft, qRight, ans, node * 2, left, (left + right) / 2);
    rangeQuery(qLeft, qRight, ans, node * 2 + 1, ((left + right) / 2) + 1, right);
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    int N, M, a, b;
    cin >> N >> M;

    for(int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    build(1, 0, N - 1);

    while(M--) {
        cin >> a >> b;

        pii ans = {-1, INT32_MAX};
        rangeQuery(a - 1, b - 1, ans, 1, 0, N - 1);

        cout << ans.MIN << ' ' << ans.MAX << '\n';
    }
}