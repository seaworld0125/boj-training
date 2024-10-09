#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {ios::sync_with_stdio(false); cin.tie(NULL);

    int N, L;
    cin >> N >> L;

    vector<pair<int, int>> v;

    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        v.emplace_back(a, b);
    }
    sort(v.begin(), v.end());

    int res = 0, cur = 0;

    for(int i = 0; i < N; i++) {
        cur = max(cur, v[i].first);

        int diff = v[i].second - cur;
        int cnt = (diff + L - 1) / L;
        cur += cnt * L;
        res += cnt;
    }
    cout << res;
}