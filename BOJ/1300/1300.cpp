#include <iostream>
using namespace std;

int main() {
    int N, k;
    cin >> N >> k;

    int result;
    int start = 0, end = k;
    while(start <= end) {
        int mid = (start + end) / 2;

        int cnt = 0;
        for(int i = 1; i <= N; i++) 
            cnt += min(mid / i, N);
        
        if(cnt < k) {
            start = mid + 1;
        }
        else {
            result = mid;
            end = mid - 1;
        }
    }
    cout << result;
}