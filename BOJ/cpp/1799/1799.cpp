#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int N;
bool board[10][10];
bool d[20] = {0}; // 왼쪽으로 기운 대각선

inline bool checkOverlap(int y, int x) {
    return board[y][x] && !d[x - y - N];
}

// 오른쪽으로 기울어진 대각선 하나씩 탐색
int recursive(int n) {
    if(n >= 2 * N - 1) return 0;

    int sum = -1;
    int y = (n < N ? n : N - 1);
    int x = (n < N ? 0 : n - N + 1);
    
    while(y >= 0 && x < N) {
        if(checkOverlap(y, x)) {
            d[x - y - N] = true;
            sum = max(sum, recursive(n + 2) + 1);
            d[x - y - N] = false;
        }
        y--;
        x++;
    }
    if(sum == -1) sum = recursive(n + 2);

    return sum;
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }
    cout << recursive(0) + recursive(1);
}