#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

#define F first
#define S second
#define pii pair<int, int>

int N;
int arr[1000001];
pii order[1000001];

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> N;
    
    int count = -1;
    int tmp;

    for(int i = 0; i < N; i++) {
        cin >> tmp;
    
        if(count == -1) {
            arr[++count] = tmp;
            order[i] = {tmp, count};
            continue;
        }

        if(arr[count] > tmp) { // 마지막 원소보다 작다면
            int idx = lower_bound(arr, arr + count, tmp) - arr;
            arr[idx] = tmp;
            order[i] = {tmp, idx};
            continue;
        }

        if(arr[count] < tmp) { // 마지막 원소보다 크다면
            arr[++count] = tmp;
        }
        order[i] = {tmp, count};
    }

    cout << count + 1 << "\n";

    stack<int> ans;

    for(int i = N - 1; i >= 0 && count >= 0; i--) {
        if(order[i].S == count) {
            ans.emplace(order[i].F);
            count--;
        }
    }

    while(!ans.empty()) {
        cout << ans.top() << ' ';
        ans.pop();
    }
}