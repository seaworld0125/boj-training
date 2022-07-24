#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int N, M, H, ans = 1e9;
bool bridgeMap[31][11];

bool checkAns() {
    for(int j = 0; j < N; j++) {
        int now = j;
        for(int i = 0; i < H; i++) {
            if(bridgeMap[i][now]) {
                now++;
            }
            else if(now > 0 && bridgeMap[i][now - 1]) {
                now--;
            }
        }
        if(now != j) return false;
    }
    return true;
}

void solve(int colIndex, int rowIndex, int bridgeCount) {

    if(bridgeCount > 3 || ans < bridgeCount) {
        return;
    }
    else if(rowIndex == H) {
        if(checkAns()) {
            ans = min(ans, bridgeCount);
        }
        return;
    }

    for(int i = colIndex; i < N - 1; i++) {
        if(!bridgeMap[rowIndex][i] && !bridgeMap[rowIndex][i + 1]) {
            bridgeMap[rowIndex][i] = true;

            solve(i + 2, rowIndex, bridgeCount + 1);

            bridgeMap[rowIndex][i] = false;
        }
    }
    solve(0, rowIndex + 1, bridgeCount);
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> N >> M >> H;

    if(M == 0) {
        cout << 0;
        return 0;
    }

    int a, b;
    for(int i = 0; i < M; i++) {
        cin >> a >> b;

        bridgeMap[a - 1][b - 1] = true;
    }

    solve(0, 0, 0);

    if(ans == 1e9)
        cout << -1;
    else
        cout << ans;
}