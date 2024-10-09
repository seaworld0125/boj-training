#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
vector<int> edges[51];

int solve(int now) {
    int time = 0;
    vector<int> child;
    for(int i = 0; i < edges[now].size(); i++) 
        child.emplace_back(solve(edges[now][i]));
    sort(child.begin(), child.end(), greater<int>());

    for(int i = 0; i < child.size(); i++) {
        time = max(time, child[i] + i + 1);
    }
    return time;
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 0; i < N; i++) {
        int a;
        cin >> a;

        if(a == -1) continue;
        edges[a].emplace_back(i);
    }
    cout << solve(0);
}