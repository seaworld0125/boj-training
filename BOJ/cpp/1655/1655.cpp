#include <iostream>
#include <queue>
using namespace std;

#define endl '\n'

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    priority_queue<int, vector<int>, less<int>> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;

    int N;
    cin >> N;

    int mid, tmp;
    for(int i = 0; i < N; i++) {
        if(i == 0) {
            cin >> mid;
            cout << mid << endl;
        }
        else {
            cin >> tmp;

            if(tmp >= mid) {
                minHeap.emplace(tmp);
                if(minHeap.size() > maxHeap.size()) {
                    maxHeap.emplace(mid);
                    mid = minHeap.top();
                    minHeap.pop();
                }
            }
            else {
                maxHeap.emplace(tmp);
                if(maxHeap.size() > minHeap.size()) {
                    minHeap.emplace(mid);
                    mid = maxHeap.top();
                    maxHeap.pop();
                }
            }

            if(minHeap.size() >= maxHeap.size())
                cout << mid << endl;
            else
                cout << maxHeap.top() << endl;
        }
    }
}