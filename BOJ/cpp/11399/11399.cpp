#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    int N;
    cin >> N;
    vector<int> v(N);

    for(int i = 0; i < N; i++) cin >> v[i];

    sort(v.begin(), v.end());

    int ans = v[0];
    for(int i = 1; i < N; i++) {
        v[i] = v[i] + v[i - 1];
        ans += v[i];
    }
    cout << ans;
}