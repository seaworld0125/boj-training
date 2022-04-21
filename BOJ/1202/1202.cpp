#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;

#define pii pair<int, int>
#define F first
#define S second

int N, K; // 보석 개수, 가방 개수
vector<pii> jewelry;
multiset<int> bag;

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> N >> K;

    int M, V; // 보석 무게, 가격
    int C;    // 가방에 담을 수 있는 최대 무게

    for(int i = 0; i < N; i++) {
        cin >> M >> V;
        jewelry.emplace_back(M, V);
    }

    for(int i = 0; i < K; i++) {
        cin >> C;
        bag.emplace(C);
    }

    sort(jewelry.begin(), jewelry.end(), [](pii& a, pii& b)  {
        return a.S > b.S;
    });

    long long ans = 0;
    multiset<int>::iterator setItr;

    int size = jewelry.size();
    for(int i = 0; i < size && !bag.empty(); i++) {
        int value = jewelry[i].S;
        int weight = jewelry[i].F;

        setItr = bag.lower_bound(weight);

        if(setItr != bag.end()) {
            bag.erase(setItr);
            ans += value;
        }
    }
    cout << ans;
}