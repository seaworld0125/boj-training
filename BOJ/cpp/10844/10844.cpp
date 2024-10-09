#include <iostream>
#include <cstring>
using namespace std;

#define INF (int)1e9

long long N, ans, dp[10][101];

int recursive(int pos, int num) {
    if(!pos) return 0;

    if(dp[num][pos]) return dp[num][pos];

    if(pos == 1) return 1; // 1의 자리수에 도착하면 1반환

    // 10보다 작을 때
    if(num + 1 < 10) 
        dp[num][pos] += (recursive(pos - 1, num + 1) % INF); 

    // num - 1이 0보다 크거나 1의 자리수가 아닐 때
    if(num - 1 > 0 || (num - 1 == 0 && N > 1)) 
        dp[num][pos] += (recursive(pos - 1, num - 1) % INF);

    return dp[num][pos]; 
}

int main() {
    cin >> N;

    memset(dp[0], 0, sizeof(dp));
    
    for(int i = 1; i < 10; i++) {
        ans += recursive(N, i);
        ans %= INF;
    }
    cout << ans;
}