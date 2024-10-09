#include <iostream>
#include <queue>
using namespace std;

#define endl '\n'

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N;
    cin >> N;

    priority_queue<int, vector<int>, greater<int>> minHeap;
    priority_queue<int, vector<int>, less<int>> maxHeap;

    for(int i = 0; i < N; i++) {
        int opt;
        cin >> opt;

        if(opt) {
            opt > 0 ? minHeap.emplace(opt) : maxHeap.emplace(opt);    
        }
        else {
            if(minHeap.empty() && maxHeap.empty()) cout << 0 << endl;
            else if(minHeap.empty()) {
                cout << maxHeap.top() << endl;
                maxHeap.pop();
            }
            else if(maxHeap.empty()) {
                cout << minHeap.top() << endl;
                minHeap.pop();
            }
            else {
                int min = minHeap.top();
                int max = maxHeap.top();

                if(-max <= min) {
                    cout << max << endl;
                    maxHeap.pop();
                }
                else {
                    cout << min << endl;
                    minHeap.pop();
                }
            }
        }
    }
}