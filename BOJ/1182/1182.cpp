#include <iostream>
using namespace std;

int N, S,
    arr[20],
    ans = 0;

void getAns(int sum, int idx) {
    sum += arr[idx];
    if(sum == S) ans++;

    if(idx + 1 < N) {
        getAns(sum - arr[idx], idx + 1);
        getAns(sum, idx + 1);
    } 
}

int main() {
    cin >> N >> S;

    for(int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    getAns(0, 0);
    cout << ans;
}