#include <iostream>
#include <queue>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, L;
    cin >> N >> L;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    for (int i = 0; i < N; i++) {

        int a, b;
        cin >> a >> b;
        pq.emplace(a, b);
    }

    int cnt = 0;
    int i = 0;

    while(!pq.empty()) {

        auto p = pq.top();
        pq.pop();
        i = max(i, p.first);

        while(i < p.second) {

            i += L;
            cnt++;
        }
    }
    cout << cnt;
}