#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

/*
    완전 탐색(x)  
*/

#define F first
#define S second

int N, M, K;
unordered_map<string, pair<int, int>> patternMap; 

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> N >> M;
    string str;
    for(int i = 0; i < N; i++) {
        
        cin >> str;
        patternMap[str].F++;

        int size = str.size();
        int count = 0;
        for(int j = 0; j < size; j++) {
            
            if(str[j] == '0') count++;
        }
        patternMap[str].S = count;
    }
    cin >> K;

    int ans = 0;
    for(auto data : patternMap) {

        int count = data.S.S;
        if(count <= K && (count % 2 == K % 2)) 
            ans = max(ans, data.S.F);
    }
    cout << ans;
}