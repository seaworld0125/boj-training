#include <iostream>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <bitset>
using namespace std;

#define pii pair<int, int>
#define F first
#define S second
#define endl '\n'
#define INF (int)1e9

/*
    [접근법 설계]

    이 문제는 5 x 5 사이즈의 맵을 이용하고 지나온 위치는 다시 돌아갈 수 없다는 조건 때문에
    탐색해야하는 가지 수가 그렇게 많지 않아 완전 탐색이 가능하다.

    1. 재귀 탐색으로 완전 탐색을 수행한다.

    2. 다음과 같은 재귀 함수를 정의한다. 
        recursive(board, y, x, oppy, oppx) = {true/false, result}
            y, x의 위치에서 최선의 플레이 시 승리 여부와 턴 수를 반환하는 재귀 함수

    2-1. 플레이어가 두 명이기 때문에 재귀 함수를 두 개 선언하거나 하나의 재귀 함수에 수많은 if문을 넣어야할 수도 있는데,
        플레이어 좌표 매개변수의 순서를 번갈아가며 전달하면 코드의 양을 줄일 수 있다. 

    2-2. 기저 사례는 문제에서 언급한 두 가지 조건을 사용한다. 자신의 차례일 때 움직일 수 없다면 패배하고,
        움직일 수 있으면서 둘이 같은 발판에 있다면 한 사람이 움직였을 때 다른 사람은 패배한다.

    2-3. 기저 사례에 해당하지 않는 경우 모든 경우의 수를 탐색하여 해당 턴에서 승리할 수 있을 시에는 최소 턴 수를 반환하고
        무조건 패배할 시에는 최대 턴 수를 함께 반환한다.
*/

/*
    [풀이 분석]

    시간 복잡도를 분석해보자.
    전체 노드의 개수는 N이라고 한다.
    
    이 풀이의 재귀 함수는 게임이 끝날 때 까지 모든 4방향에 대해서 탐색을 이어나가야 한다.
    
    즉, T(N)을 재귀 함수의 시간 복잡도라고 한다면, T(N) = 4T(N - 1)이라고 할 수 있다.
    이 재귀 식을 무한히 모두 풀어 헤처보자.

    T(N) = 4(4T(N - 2)) = (4^2)T(N - 2) = ... = (4^k)T(N - K) 
    N - K == 1이라고 한다면, T(N) = (4^(N - 1))T(1) = O(4^N) 이라고 할 수 있다.

    이 문제는 하나의 경로에서 방문한 노드에는 다시 방문할 수 없기 때문에 탐색해야할 경우의 수가 크게 줄어들고, 
    N의 크기가 최대 5이기 때문에 최악의 경우에도 이 풀이로 풀이가 가능함을 알 수 있다. 
*/

int dy[] = {1, -1, 0, 0};
int dx[] = {0, 0, 1, -1};

int MAX_COL, MAX_ROW;

struct Status {
    bool win;
    int move;
    Status(bool win_, int move_):win(win_), move(move_) {}
};

inline bool outOfRange(int& y, int& x) {
    if(y < 0 || x < 0 || y >= MAX_ROW || x >= MAX_COL) return true;
    return false;
}

bool stuck(vector<vector<int>>& board, int& y, int& x) {
    for(int i = 0; i < 4; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];

        if(outOfRange(ny, nx) || !board[ny][nx]) continue;
        return false;
    }
    return true;
}

Status solve(vector<vector<int>>& board, int y, int x, int oppy, int oppx) {

    if(stuck(board, y, x)) return Status(false, 0);
    if(y == oppy && x == oppx) return Status(true, 1);

    bool canWin = false;
    int minMove = INF, maxMove = 0;

    for(int i = 0; i < 4; i++) {

        int ny = y + dy[i];
        int nx = x + dx[i];
        if(outOfRange(ny, nx) || !board[ny][nx]) continue;

        board[y][x] = 0;
        auto result = solve(board, oppy, oppx, ny, nx);
        board[y][x] = 1;

        if(!result.win) {
            canWin = true;
            minMove = min(minMove, result.move);
        }
        else if(!canWin){ 
            maxMove = max(maxMove, result.move);
        }
    }
    return Status(canWin, (canWin ? minMove : maxMove) + 1);
}   

int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {

    MAX_COL = board[0].size();
    MAX_ROW = board.size();

    return solve(board, aloc[0], aloc[1], bloc[0], bloc[1]).move;
}

int main() {
    vector<vector<vector<int>>> board = {
        {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
        {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}},
        {{1, 1, 1, 1, 1}},
        {{1}}
    };
    vector<vector<int>> aloc = {
        {1, 0},
        {1, 0},
        {0, 0},
        {0, 0}
    };
    vector<vector<int>> bloc = {
        {1, 2},
        {1, 2},
        {0, 4},
        {0, 0}
    };

    for(int i = 0; i < board.size(); i++) {
        printf("result is %d\n=========================\n\n", solution(board[i], aloc[i], bloc[i]));
    }
}