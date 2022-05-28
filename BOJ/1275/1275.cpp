#include <iostream>
#include <algorithm>
using namespace std;

#define ll long long

int N, Q, x, y, a, b;
int arr[100001];
ll tree[400000];

struct SegmentTree {
    ll build(int node, int left, int right) {
        if(left == right) {
            return tree[node] = arr[left];
        }

        int mid = (left + right) / 2;
        ll lVal = build(node * 2, left, mid);
        ll rVal = build(node * 2 + 1, mid + 1, right);

        return tree[node] = lVal + rVal;
    }

    ll rangeQuery(const int& qLeft, const int& qRight, int node, int left, int right) {
        if(right < qLeft || qRight < left) {
            return 0;
        }
        if(qLeft <= left && right <= qRight) {
            return tree[node];
        }

        int mid = (left + right) / 2;
        ll lVal = rangeQuery(qLeft, qRight, node * 2, left, mid);
        ll rVal = rangeQuery(qLeft, qRight, node * 2 + 1, mid + 1, right);

        return lVal + rVal;
    }

    ll updateQuery(const int& updateVal, const int& idx, int node, int left, int right) {
        if(idx < left || right < idx) {
            return tree[node];
        }

        if(left == right) {
            return tree[node] = updateVal;
        }

        int mid = (left + right) / 2;
        ll lVal = updateQuery(updateVal, idx, node * 2, left, mid);
        ll rVal = updateQuery(updateVal, idx, node * 2 + 1, mid + 1, right);

        return tree[node] = lVal + rVal;
    }
};

int main() {
    scanf("%d %d", &N, &Q);

    for(int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    SegmentTree segmentTree;
    segmentTree.build(1, 0, N - 1);

    for(int i = 0; i < Q; i++) {
        scanf("%d %d %d %d", &x, &y, &a, &b);

        if(x > y) swap(x, y);

        printf("%lld\n", segmentTree.rangeQuery(x - 1, y - 1, 1, 0, N - 1));
        segmentTree.updateQuery(b, a - 1, 1, 0, N - 1);
    }
}