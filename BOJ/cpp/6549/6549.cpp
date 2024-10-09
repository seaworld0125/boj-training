#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define ll long long

struct SegmentTree
{
    int size;
    vector<int> tree;
    vector<ll> arr;

    int build(int node, int left, int right) {
        if(left == right) {
            return tree[node] = left; // index를 저장
        }
        int mid = (left + right) / 2;
        int lVal = build(node * 2, left, mid);
        int rVal = build(node * 2 + 1, mid + 1, right);

        return tree[node] = (arr[lVal] < arr[rVal] ? lVal : rVal);
    }

    void input(int size) {
        this->size = size;
        this->tree.resize(size * 4, 0);
        this->arr.resize(size, 0);

        for(int i = 0; i < size; i++) {
            cin >> arr[i];
        }
    }

    // [qLeft, qRignt] 구간에서의 최소 높이 index를 구한다
    int rangeQuery(int qLeft, int qRight, int node, int left, int right) {
        if(qRight < left || right < qLeft) {
            return -1;
        }

        if(qLeft <= left && right <= qRight) {
            return tree[node];
        }

        int mid = (left + right) / 2;
        int lVal = rangeQuery(qLeft, qRight, node * 2, left, mid);
        int rVal = rangeQuery(qLeft, qRight, node * 2 + 1, mid + 1, right);
        
        if(lVal == -1) return rVal;
        else if(rVal == -1) return lVal;
        else return arr[lVal] < arr[rVal] ? lVal : rVal;
    }

    // [i, j] 구간에서의 최대 넓이를 구한다.
    ll solve(int i, int j) {
        ll maxWidth, tmpWidth;
        int minIndex = rangeQuery(i, j, 1, 0, size - 1);

        maxWidth = ((ll)j - i + 1) * (ll) arr[minIndex];

        // minIndex 기준 왼쪽으로 더 탐색할 수 있다면
        if(i < minIndex) {
            tmpWidth = solve(i, minIndex - 1);
            maxWidth = max(maxWidth, tmpWidth);
        }
        
        // minIndex 기준 오른쪽으로 더 탐색할 수 있다면
        if(minIndex < j) {
            tmpWidth = solve(minIndex + 1, j);
            maxWidth = max(maxWidth, tmpWidth);
        }

        return maxWidth;
    }
};

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    int T, H;

    SegmentTree segTree;
    while(1) {
        cin >> T;
        if(!T) break;

        segTree.input(T);
        segTree.build(1, 0, T - 1);
        cout << segTree.solve(0, T - 1) << endl;
    }
}