#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define ll long long

ll T;
int n, num;
vector<int> A, B;
vector<ll> sumA, sumB;

void getSum() {
    int size = A.size();
    ll sum;

    for(int i = 0; i < size; i++) {
        sum = 0;
        for(int j = i; j < size; j++) {
            sum += A[j];
            sumA.emplace_back(sum);
        }
    }

    size = B.size();
    for(int i = 0; i < size; i++) {
        sum = 0;
        for(int j = i; j < size; j++) {
            sum += B[j];
            sumB.emplace_back(sum);
        }
    }
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> T;

    cin >> n;
    A.resize(n);
    for(int j = 0; j < n; j++) {
        cin >> A[j];
    }
    cin >> n;
    B.resize(n);
    for(int j = 0; j < n; j++) {
        cin >> B[j];
    }

    getSum();

    sort(sumA.begin(), sumA.end());
    sort(sumB.begin(), sumB.end());

    ll ans = 0;

    for(int i = 0; i < sumA.size(); i++) {
        ll sub = T - sumA[i];
        ll lb = lower_bound(sumB.begin(), sumB.end(), sub) - sumB.begin();
        ll ub = upper_bound(sumB.begin(), sumB.end(), sub) - sumB.begin();

        ans += (ub - lb);
    }
    cout << ans;
}