#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

#define pii pair<int, int>
#define F first
#define S second
#define INF (int)1e9

int dy[] = {1, 0, -1, 0};
int dx[] = {0, 1, 0, -1};

/*
    https://school.programmers.co.kr/learn/courses/30/lessons/72415
    
    1차시도 66.7 
    2차시도 100 
*/

struct moveData {
    int y;
    int x;
    int move;
};

inline bool outOfRange(int y, int x) {
    if(y < 0 || x < 0 || y >= 4 || x >= 4) return true;
    return false;
}

int nr, nc;
int move(int target, vector<vector<int>>& board) {
    queue<moveData> visit;
    bool visited[4][4];
    memset(visited[0], 0, sizeof(visited));

    visit.push({nr, nc, 0});
    visited[nr][nc] = true;

    while(!visit.empty()) {

        auto pos = visit.front();
        visit.pop();

        if(board[pos.y][pos.x] == target) {
            board[pos.y][pos.x] = 0;
            nr = pos.y;
            nc = pos.x;
            return pos.move + 1;
        }

        for(int i = 0; i < 4; i++) { // ctrl + 방향키
            int y = pos.y + dy[i], 
                x = pos.x + dx[i];
            
            while(1) {
                if(outOfRange(y, x)) {
                    y -= dy[i],
                    x -= dx[i];

                    if(!visited[y][x]) {
                        visit.push({y, x, pos.move + 1});
                        visited[y][x] = true;
                    }
                    break;
                }
                else if(board[y][x]) {
                    if(!visited[y][x]) {
                        visit.push({y, x, pos.move + 1});
                        visited[y][x] = true;
                    }
                    break;
                }
                y += dy[i];
                x += dx[i];
            }
        }

        for(int i = 0; i < 4; i++) { // 방향키
            int y = pos.y + dy[i];
            int x = pos.x + dx[i];

            if(outOfRange(y, x) || visited[y][x]) continue;

            visit.push({y, x, pos.move + 1});
            visited[y][x] = true;
        }
    }
}
int solution(vector<vector<int>> board, int r, int c) {
    int answer = INF;
    vector<vector<pii>> characterPos(7);

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(board[i][j]) {
                characterPos[board[i][j]].emplace_back(i, j);
            }
        }
    }

    vector<int> character;
    for(int i = 1; i < 7; i++) {
        if(characterPos[i].empty()) continue;

        character.emplace_back(i);
    }

    int size = character.size();
    do
    {
        vector<vector<int>> myBoard = board;
        int ans = 0;
        nr = r,
        nc = c;

        for(int i = 0; i < size; i++) {
            int idx = character[i];
            
            ans += move(idx, myBoard);
            ans += move(idx, myBoard);
        }
        answer = min(answer, ans);
    } while (next_permutation(character.begin(), character.end()));
    
    return answer;
}

int main() {
    vector<vector<vector<int>>> boards = {
        {{1,0,0,3},{2,0,0,0},{0,0,0,2},{3,0,1,0}},
        {{3,0,0,2},{0,0,1,0},{0,1,0,0},{2,0,0,3}},
        {{1,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,1}}
    };

    vector<int> r = {
        1, 
        0,
        0,
    };

    vector<int> c = {
        0, 
        1,
        3,
    };

    for(int i = 0; i < r.size(); i++) {
        // answer = INF;
        // vector<vector<pii>>().swap(characterPos);
        cout << solution(boards[i], r[i], c[i]) << endl;
    }
        // cout << solution(boards[2], r[2], c[2]) << endl;
}