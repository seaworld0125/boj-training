#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T, N;

    cin >> T;
    for(int i = 0; i < T; i++) {
        cin >> N;

        vector<pair<int, int>> v(N);

        for(int j = 0; j < N; j++)
            cin >> v[j].first >> v[j].second;

        sort(v.begin(), v.end(), [](pair<int, int> & a, pair<int, int> & b) {
            if(a.first < b.first) return true;
            else return false;
        });

        int ans = 1;
        int score = v[0].second;

        for(int j = 1; j < v.size(); j++) {
            if(v[j].second < score) {
                ans++;
                score = v[j].second;
            }
        }
        cout << ans << endl;
    }
}