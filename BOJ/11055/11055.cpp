#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define F first
#define S second

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    int N;
    cin >> N;

    vector<pair<int, int>> lis;
    
    int num, 
        maxSum,
        ans = 0;

    for(int i = 0; i < N; i++) {
        cin >> num;

        maxSum = num;
        for(int j = 0; j < lis.size(); j++) {
            if(num > lis[j].F) {
                maxSum = max(maxSum, lis[j].S + num);
            }
        }
        lis.emplace_back(num, maxSum);
        ans = max(ans, maxSum);
    }
    cout << ans;
}