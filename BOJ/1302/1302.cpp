#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

#define endl '\n'

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    // input
    int N;
    cin >> N;

    // var
    map<string, int> bookMap;
    string tmp;

    // input, find and insert
    for(int i = 0; i < N; i++) {
        cin >> tmp;
        
        // if exist
        if(bookMap.find(tmp) != bookMap.end()) {
            bookMap[tmp]++;
        }
        else {
            bookMap.emplace(tmp, 1);
        }
    }

    // map to vector
    vector<pair<string, int>> v(bookMap.begin(), bookMap.end());

    // sorting
    sort(v.begin(), v.end(), [](pair<string, int> & a, pair<string, int> & b) {
        if(a.second > b.second) return true;
        else if(a.second == b.second){
            return a.first < b.first;
        }
        return false;
    });

    // print
    cout << v[0].first;
}