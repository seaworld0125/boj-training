#include <iostream>
#include <vector>
using namespace std;

int binarySearch(int num, int size, vector<int> & dp) {
    int left = 0, right = size, mid;

    while(left < right) {
        mid = (left + right) / 2;
        if(dp[mid] < num)
            left = mid + 1;
        else
            right = mid;
    }
    cout << "right >> " << right << endl;
    return right;
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    int N;
    cin >> N;

    vector<int> arr(N);
    for(int i = 0; i < N; i++) cin >> arr[i];

    int size = 0;
    vector<int> dp(N);
    dp[0] = arr[0];

    for(int i = 1; i < N; i++) {
        if(dp[size] < arr[i]) {
            size++;
            dp[size] = arr[i];
        }
        else {
            dp[binarySearch(arr[i], size, dp)] = arr[i];
        }
    }
    cout << size + 1;
}