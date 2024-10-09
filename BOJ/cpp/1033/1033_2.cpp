#include <iostream>
#include <vector>
using namespace std;

#define ll long long

ll getGcd(ll a, ll b) {
    ll r;
    
    if(a < b) {
        r = a;
        a = b;
        b = r;
    }

    while(b != 0) {
        r = a % b;
        a = b; 
        b = r;
    }
    return a;
}

ll getLcm(ll a, ll b) {
    return (a * b) / getGcd(a, b);
}

pair<ll, ll> getRatio(ll a, ll b) {
    ll lcm = getLcm(a, b);

    return {lcm / a, lcm / b};
} 

int main() {
    ll ratios[11][11];
    ll ans[11];
    vector<int> edges[11];

    int N;
    cin >> N;

    int a, b, p, q;

    fill_n(ans, N, 1);
    fill_n(ratios[0], 11 * 11, 0);

    for(int i = 0; i < N - 1; i++) {
        cin >> a >> b >> p >> q;

        edges[a].emplace_back(b);
        edges[b].emplace_back(a);

        if(p == q) {
            ratios[a][b] = 1;
            ratios[b][a] = 1;
            continue;
        }

        ratios[a][b] = p;
        ratios[b][a] = q;

        auto ratio = getRatio(p, q);

        ans[a] = getLcm(ans[a], ratio.second);
        ans[b] = getLcm(ans[b], ratio.first);
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < edges[i].size(); j++) {

            int num = edges[i][j];

            a = ans[i] * ratios[num][i]; 
            b = ans[num] * ratios[i][num]; 

            if(a == b) continue; // 비율을 만족함

            auto ratio = getRatio(a, b);

            ans[i] *= ratio.first;
            ans[num] *= ratio.second; 
        }
    }

    for(int i = 0; i < N; i++) { 
        cout << ans[i] << ' ';
    }
}