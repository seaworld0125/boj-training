#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

#define ll long long
#define endl '\n'

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    // input
    int N;
    cin >> N;

    // var
    vector<ll> v(N);
    int idx[3];
    ll ans = (ll)1e10;

    // input num, num to Num
    for(int i = 0; i < N; i++)
        cin >> v[i];
    
    // sorting
    sort(v.begin(), v.end());

    // choose one
    for(int i = 0; i < N; i++) {
        int left = 0, right = N - 1;

        // choose two
        while(left < right) {
            if(left != i && right != i) {
                ll sum = v[i] + v[left] + v[right];

                if(ans > abs(sum)) {
                    ans = abs(sum);
                    idx[0] = i;
                    idx[1] = left;
                    idx[2] = right;
                };
            }
            if(abs(v[i] + v[left + 1] + v[right]) > abs(v[i] + v[left] + v[right - 1]))
                right--;
            else
                left++;            
        }                           
    }

    // sorting
    sort(idx, idx + 3);

    // print
    cout << v[idx[0]] << ' ' << v[idx[1]] << ' ' << v[idx[2]];
}