#include <iostream>
#include <cmath>
using namespace std;

int N;
int ans = 0;

int C[15];

bool check(int L) {
    for(int i = 0; i < L; i++) { // 행
        if(C[i] == C[L] || (abs(C[i] - C[L]) == L - i)) return false;
    }
    return true;
}

void solve(int L) { // 한 행씩 올라감
    if(L == N) ans++;

    for(int i = 0; i < N; i++) {
        C[L] = i;

        if(check(L)) solve(L + 1);
    }
}

int main() {
    cin >> N;
    solve(0);
    cout << ans;
}