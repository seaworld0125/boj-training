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

int changeDegree[1001][1001];

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    int answer = 0;

    int skillSize = skill.size(); // worst = 250,000
    int N = board.size(); // 행 // worst = 1000
    int M = board[0].size(); // 열 // worst = 1000

    memset(changeDegree[0], 0, sizeof(changeDegree));

    // 변화량 누적 배열 생성
    for(int i = 0; i < skillSize; i++) { // worst = skillSize

        int degree = skill[i][5] * (skill[i][0] == 1 ? -1 : 1);
        int r1 = skill[i][1];
        int c1 = skill[i][2];
        int r2 = skill[i][3];
        int c2 = skill[i][4];

        changeDegree[r1][c1] += degree;
        changeDegree[r1][c2 + 1] -= degree;
        changeDegree[r2 + 1][c1] -= degree;
        changeDegree[r2 + 1][c2 + 1] += degree;
    }

    // 왼쪽에서 오른쪽으로 누적
    for(int i = 0; i < N; i++) { // 끝 변화량은 사실 의미 없다. // worst = N * M
        for(int j = 1; j < M; j++) {
            changeDegree[i][j] += changeDegree[i][j - 1];  
        }
    }

    // 위에서 아래로 누적
    for(int i = 0; i < M; i++) { // worst = N * M
        for(int j = 1; j < N; j++) {
            changeDegree[j][i] += changeDegree[j - 1][i];  
        }
    }

    // 원본 배열과 합을 구함
    for(int i = 0; i < N; i++) { // worst = N * M
        for(int j = 0; j < M; j++) {
            if(board[i][j] + changeDegree[i][j] > 0) {
                answer++;
            }
        }
    }

    // O(3NM + skillSize)
    // worst = 3,000,000 + 250,000 = 3,250,000

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
        int result = solution(boards[i], skills[i]);
        cout << result << endl;
    }
}