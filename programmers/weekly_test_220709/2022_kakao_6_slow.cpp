#include <iostream>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
using namespace std;

#define pii pair<int, int>
#define F first
#define S second

#define endl '\n'

void printBoard(int boardLength, int boardWidth, vector<vector<int>>& board) {
    for(int i = 0; i < boardLength; i++) {
        for(int j = 0; j < boardWidth; j++) {
            cout << board[i][j] << '\t';
        }cout << "\n\n";
    }
}

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    int answer = 0;

    int skillSize = skill.size(); // worst = 250,000
    int boardLength = board.size(); // worst = 1000
    int boardWidth = board[0].size(); // worst = 1000

    pii posMin, posMax;

    for(int i = 0; i < skillSize; i++) { // worst = 250,000 * 1000 * 1000 = 250,000,000,000

        posMin = {skill[i][1], skill[i][2]};
        posMax = {skill[i][3], skill[i][4]};

        for(int j = posMin.F; j <= posMax.F; j++) {
            for(int k = posMin.S; k <= posMax.S; k++) { 

                board[j][k] += skill[i][5] * (skill[i][0] == 1 ? -1 : 1);
            }   
        }
    }

    for(int i = 0; i < boardLength; i++) {
        for(int j = 0; j < boardWidth; j++) {
            if(board[i][j] > 0) {
                answer++;
            } 
        }
    }

    printBoard(boardLength, boardWidth, board);

    return answer;
}

int main() {
    vector<vector<vector<int>>> boards = {
        {{5, 5, 5, 5, 5}, {5, 5, 5, 5, 5}, {5, 5, 5, 5, 5}, {5, 5, 5, 5, 5}},
        {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}
    };

    vector<vector<vector<int>>> skills = {
        {{1, 0, 0, 3, 4, 4}, {1, 2, 0, 2, 3, 2}, {2, 1, 0, 3, 1, 2}, {1, 0, 1, 3, 3, 1}},
        {{1, 1, 1, 2, 2, 4}, {1, 0, 0, 1, 1, 2}, {2, 2, 0, 2, 0, 100}}
    };

    for(int i = 0; i < boards.size(); i++) {

        solution(boards[i], skills[i]);
    }
}