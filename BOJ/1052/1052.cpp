#include <bitset>
#include <iostream>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;

    int ans = 0;
    int bottleCount = bitset<24>(N).count();

    int lastBit;
    while(K < bottleCount) {
        lastBit = (int)(N & -N);
        ans += lastBit;
        N += lastBit;
        bottleCount = bitset<24>(N).count();
    }
    cout << ans;
}