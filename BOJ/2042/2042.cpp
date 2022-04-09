#include <iostream>
#include <vector>
using namespace std;

#define ll long long
#define MAX 1000001

ll originalArr[MAX];
int N, M, K;

ll arr[MAX] = {0};

struct BinaryIndexedTree {

    BinaryIndexedTree() {
        for(int i = 1; i <= N; i++) {
            this->update(i, originalArr[i]);
        }
    }

    void update(const int& originalIdx, const ll& updateNum) {
        int idx = originalIdx;

        while(idx <= N) {
            arr[idx] += updateNum;
            idx += (idx & -idx);
        }
    }

    ll getSum(int idx) {
        if(idx == 0) return 0;
        ll sum = 0;

        while(idx > 0) {
            sum += arr[idx];
            idx -= (idx & -idx);
        }

        return sum;
    }

    ll rangeSum(int start, int end) {
        return this->getSum(end) - this->getSum(start - 1);
    }
};

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> N >> M >> K;

    for(int i = 1; i <= N; i++) {
        cin >> originalArr[i];
    }

    BinaryIndexedTree BIT;

    ll a, b, c;
    for(int i = 0; i < M + K; i++) {
        cin >> a >> b >> c; 

        if(a == 1) {
            BIT.update(b, c - originalArr[b]); 
            originalArr[b] = c;
        }
        else {
            cout << BIT.rangeSum(b, c) << endl; 
        } 
    }
}   