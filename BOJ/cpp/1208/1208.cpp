#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define INF (int)1e9

int N, S;
int arr[41];
vector<int> A, B;
long long int ans = 0;

void getA(int sum, int idx) { // 전체 부분수열의 합을 구한다
    if(idx >= N/2) return;

    sum += arr[idx];
    if(sum == S) ans++; // 부분수열의 합이 구하고자하는 답과 같다면 ans를 증가시킨다

    A.emplace_back(sum);
    getA(sum - arr[idx], idx + 1);
    getA(sum, idx + 1);
}

void getB(int sum, int idx) {
    if(idx >= N) return;

    sum += arr[idx];
    if(sum == S) ans++;

    B.emplace_back(sum);
    getB(sum - arr[idx], idx + 1);
    getB(sum, idx + 1);
}

void getAB() {
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    for(int i = 0; i < A.size(); i++) {
        int sub = S - A[i];

        int lb = lower_bound(B.begin(), B.end(), sub) - B.begin();
        int ub = upper_bound(B.begin(), B.end(), sub) - B.begin();

        ans += ub - lb;
    }
}

int main() {
    cin >> N >> S;

    for(int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    getA(0, 0);
    getB(0, N/2);
    getAB();

    cout << ans;
}