#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    int N;
    cin >> N;

    vector<int> v(N);

    for(int i = 0; i < N; i++) {
        cin >> v[i];
    } 
    reverse(v.begin(), v.end());

    vector<int> ans;
    ans.emplace_back(v[0]);

    for(int i = 1; i < N; i++) { // LIS
        auto it = lower_bound(ans.begin(), ans.end(), v[i]);            

        if(it == ans.end()) {
            ans.emplace_back(v[i]);
        }
        else {
            ans[it - ans.begin()] = v[i];
        }
    }
    cout << ans.size();
}