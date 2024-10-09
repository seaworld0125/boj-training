#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, idx;
    cin >> N;

    vector<int> ports(N);
    vector<int> lis;

    for(int i = 0; i < N; i++) {
        cin >> ports[i];

        if(lis.empty()) 
            lis.emplace_back(ports[i]);
        else {
            idx = lower_bound(lis.begin(), lis.end(), ports[i]) - lis.begin();
            
            if(idx == lis.size())
                lis.emplace_back(ports[i]);
            else
                lis[idx] = ports[i];
        }
    }  
    cout << lis.size();
}