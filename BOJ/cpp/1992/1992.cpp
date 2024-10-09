#include <iostream>
#include <queue>
using namespace std;

bool map[65][65];

void recursive(int y, int x, int len) {
    bool tf = map[y][x];
    bool flag = true;

    for(int i = y; i < len + y && flag; i++) {
        for(int j = x; j < len + x && flag; j++) {
            if(tf != map[i][j]) {   
                flag = false;
            }
        }
    }

    if(flag) cout << tf;
    else { // 쪼개짐
        len /= 2; // 8 -> 4 -> 2 -> 1
        cout << '(';
        recursive(y, x, len);
        recursive(y, x + len, len);
        recursive(y + len, x, len);
        recursive(y + len, x + len, len);
        cout << ')';
    }
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    int N;
    cin >> N;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            char b;
            cin >> b;
            map[i][j] = b - '0';
        }
    }
    recursive(0, 0, N);
}