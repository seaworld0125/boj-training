#include <iostream>
#include <queue>
using namespace std;

#define endl '\n'

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N;
    cin >> N;

    priority_queue<int, vector<int>, greater<int>> pq;

    for(int i = 0; i < N; i++) {
        int opt;
        cin >> opt;

        if(opt) pq.emplace(opt);
        else {
            if(pq.empty()) cout << 0 << endl;
            else {
                cout << pq.top() << endl;
                pq.pop();
            }
        }
    }
}