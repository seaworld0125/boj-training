#include <iostream>
#include <vector>
using namespace std;

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, S;
    cin >> N >> S;

    int ans = (int)1e9;
    int sum = 0;
    
    vector<int> v(N);
    vector<pair<int,int>> point;

    for(int i = 0; i < N; i++) {
        cin >> v[i];
        sum += v[i];
        
        if(v[i] >= S) ans = 1;
    }

    if(ans == 1) {
        cout << 1;
        return 0;
    }
    if(sum < S) {
        cout << 0;
        return 0;
    }

    ans = (int)1e9;
    sum = v[0] + v[1];
    int left = 0, right = 1;

    while(left < right && right < N && left > -1) {
        if(sum <= S) {
            right++;
            sum += v[right];
        }
        else if(sum > S){
            sum -= v[left];
            left++;
        }

        if(sum >= S) {
            ans = min(ans, right - left + 1);
        }
    }
    cout << ans;
}