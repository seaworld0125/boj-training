#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

int r1, r2, c1, c2;
int ans[50][5];

int dy[] = {0, -1, 0, 1};
int dx[] = {1, 0, -1, 0};

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> r1 >> c1 >> r2 >> c2;

    int r = r2 - r1;
    int c = c2 - c1;

    int length = 1;
    int y = 0, x = 0, num = 1, dir = 0;

    int maxNum = 0;

    while(1) {
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < length; j++) {

                if(y >= r1 && x >= c1 && y <= r2 && x <= c2) {
                    ans[y - r1][x - c1] = num;
                    maxNum = max(maxNum, num);
                }
                y += dy[dir];
                x += dx[dir];
                num++;
            }
            dir++;
            dir %= 4;
        }
        length++;

        if(ans[0][0] && ans[r][c] && ans[r][0] && ans[0][c]) break;
    }

    int space = 0;
    while(maxNum) {
        maxNum /= 10;
        space++;
    }

    for(int i = 0; i <= r; i++) {
        for(int j = 0; j <= c; j++) {
            cout << setw(space) << ans[i][j] << ' ';
        }cout << endl;
    }
}