#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

#define ll long long

struct Num {
    int num;
    bool isNegative;

    Num(int n) {
        num = (n > 0 ? n : n * -1);
        isNegative = (n > 0 ? false : true); 
    }
};

int N, tmp;
vector<Num> list;

int main() {
    cin >> N;

    for(int i = 0; i < N; i++) {
        cin >> tmp;
        list.emplace_back(tmp);
    }

    sort(list.begin(), list.end(), [](Num a, Num b) {
        return a.num < b.num;
    });

    ll ans = (ll)1e10;
    int ans_a, ans_b;

    for(int i = 0; i + 1 < N; i++) {
        int a = list[i].num * (list[i].isNegative ? -1 : 1);
        int b = list[i + 1].num * (list[i + 1].isNegative ? -1 : 1);

        int sum = abs((ll)(a + b));

        if(ans > sum) {
            ans = sum;
            ans_a = a;
            ans_b = b;
        }
    }
    if(ans_a < ans_b) cout << ans_a << ' ' << ans_b;
    else cout << ans_b << ' ' << ans_a; 
}