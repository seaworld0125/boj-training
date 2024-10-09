#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    // 
    int n;
    cin >> n;

    // var
    vector<pair<int, int>> v(n); // p, d
    priority_queue<int, vector<int>, greater<int>> pq;

    // input
    for(int i = 0; i < n; i++)
        cin >> v[i].first >> v[i].second;
    
    // sorting
    sort(v.begin(), v.end(), [](pair<int, int> & a, pair<int, int> & b) {
        if(a.second < b.second) return true;
        else if(a.second == b.second) return a.first < b.first;
        else return false;
    });

    // solve
    int lastDay = 0, ans = 0;
    for(auto pd : v) {
        lastDay = max(lastDay, pd.second);

        if(pq.size() >= lastDay) {                       
            ans -= pq.top();
            pq.pop();
        }
        pq.emplace(pd.first);
        ans += pd.first;
    }
    cout << ans;
}