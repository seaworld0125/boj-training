#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int N;
bool board[10][10];
bool visited[10][10];
vector<pair<int, int>> pos; // 비숍을 놓을 수 있는 자리

#define F first
#define S second

inline bool checkOverlap(int y1, int x1, int y2, int x2) {
    return abs(y1 - y2) == abs(x1 - x2);
}

int recursive(int y, int x, int count) {
    visited[y][x] = true;

    int ans = count;
    for(int i = 0; i < pos.size(); i++) { // 다음 비숍 자리를 고름
        int y_ = pos[i].F;
        int x_ = pos[i].S;
        if(visited[y_][x_]) continue; // 다음 비숍 자리도 대각은 고를 수 없음

        bool canPut = true;
        for(int j = 0; j < pos.size(); j++) { 
            if(visited[pos[j].F][pos[j].S] && checkOverlap(y_, x_, pos[j].F, pos[j].S)) { // 놓아져 있는 비숍들 중에서 대각선에 있는지 확인
                canPut = false;
                break;
            }
        }
        if(!canPut) continue;
        ans = max(ans, recursive(y_, x_, count + 1));
    }
    visited[y][x] = false;
    return ans;
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> board[i][j];
            if(board[i][j]) pos.emplace_back(i, j);

            visited[i][j] = false;
        }
    }

    int ans = 0;
    for(int i = 0; i < pos.size(); i++) { // 시작 점
        ans = max(ans, recursive(pos[i].F, pos[i].S, 1));
    }
    cout << ans;
}