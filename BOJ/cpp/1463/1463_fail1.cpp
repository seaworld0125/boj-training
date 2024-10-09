#include <iostream>
using namespace std;

#define INF (int)1e9

int solve(int num, int target, int count) {
    if(num == target) return count;
    if(num > target) return -1;

    int a = solve(num + 1, target, count + 1);
    int b = solve(num << 2, target, count + 1);
    int c = solve(num * 3, target, count + 1);

    return min((a != -1 ? a : INF), min((b != -1 ? b : INF), (c != -1 ? c : INF)));
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);    
    int num;
    cin >> num;

    cout << solve(1, num, 0);
}
