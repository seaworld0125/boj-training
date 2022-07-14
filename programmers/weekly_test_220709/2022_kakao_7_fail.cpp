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

int dy[] = {1, -1, 0, 0};
int dx[] = {0, 0, 1, -1};

int boardMap[5][5];
bool visited[(1 << 25)] = {0};

int BOARD_ROW_SIZE;
int BOARD_COL_SIZE;

struct Data {
    pii APos;
    pii BPos;
    int ACount;
    int BCount;
    bool ATurn;

    Data(vector<int>& aloc, vector<int>& bloc) {
        APos.F = aloc[0]; // 행
        APos.S = aloc[1]; // 열
        BPos.F = bloc[0];
        BPos.S = bloc[1];

        ACount = 0;
        BCount = 0;
        ATurn = true;
    }

    Data(int ny, int nx, Data& data) {
        if(data.ATurn) {
            this->APos = {ny, nx};
            this->BPos = data.BPos;
            this->ACount = data.ACount + 1;
            this->BCount = data.BCount;
        }
        else {
            this->APos = data.APos;
            this->BPos = {ny, nx};
            this->ACount = data.ACount;
            this->BCount = data.BCount + 1;
        }
        this->ATurn = !(data.ATurn);
    }
};

struct Ans {
    int ACount;
    int BCount;
    int answer;
    Ans(int ac, int bc, int ans) : ACount(ac), BCount(bc), answer(ans) {}
};

inline bool outOfRange(int y, int x) {
    if(y < 0 || x < 0 || y >= BOARD_ROW_SIZE || x >= BOARD_COL_SIZE) return true;
    return false;
}

void renewAns(Ans& ans, Data& data) {
    ans.answer = data.ACount + data.BCount;
    ans.ACount = data.ACount;
    ans.BCount = data.BCount;

    // cout << "[renew ans] ";
    // cout << (data.ATurn ? "A" : "B") << " lose, status = " << bitset<25>(status) << endl;
    // cout << (data.ATurn ? "A" : "B") << " lose ";
    // printf("ACount = %d, BCount = %d\n\n", data.ACount, data.BCount);
}

void solve(Ans& ans, vector<vector<int>>& board, Data data, int status) {

    auto& now = (data.ATurn ? data.APos : data.BPos);
    visited[status] = true;

    // 현재 위치에서 선택가능한 모든 상태를 확인
    bool canMove = false;
    for(int i = 0; i < 4; i++) { 

        int y = now.F + dy[i];
        int x = now.S + dx[i];
        if(outOfRange(y, x) || !board[y][x]) continue;

        int newBit = (1 << boardMap[y][x]);
        if(status & newBit) continue;

        canMove = true;

        int newStatus = (status | newBit);
        if(visited[newStatus]) continue;

        solve(ans, board, Data(y, x, data), newStatus);
    }
}   

int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {
    BOARD_ROW_SIZE = board.size();
    BOARD_COL_SIZE = board[0].size();
    
    int count = 0; // 0번부터 맵핑
    for(int i = 0; i < BOARD_ROW_SIZE; i++) {
        for(int j = 0; j < BOARD_COL_SIZE; j++) {
            boardMap[i][j] = count++;
        }
    }

    Ans ans(INF, INF, INF);
    solve(ans, board, Data(aloc, bloc), (1 << boardMap[aloc[0]][aloc[1]]));

    return ans.answer;
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
        memset(visited, 0, sizeof(visited));
        printf("result is %d\n=========================\n\n", solution(board[i], aloc[i], bloc[i]));
    }
}