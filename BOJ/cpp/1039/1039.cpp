#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>
#include <cstring>
#include <algorithm>
using namespace std;

string N;
int K, len;
int ans = -1;

unordered_set<string> bucket[11];

void solve(string now, int cnt) {

    // 종료 조건 : cnt == K
    if(cnt == K) {
        ans = max(ans, stoi(now));
        return;
    }

    for(int i = 0; i < len; i++) {
        for(int j = i + 1; j < len; j++) {

            if(i == 0 && now[j] == '0') continue;

            swap(now[i], now[j]);

            // 현재 cnt에서 조사해보지 않은 경우라면 재귀 수행
            if(bucket[cnt].find(now) == bucket[cnt].end()) {
                bucket[cnt].emplace(now);
                solve(now, cnt + 1);
            }

            swap(now[j], now[i]);
        }
    }
}

int main() {
    cin >> N >> K;
    len = N.length();

    solve(N, 0);
    cout << ans;
}