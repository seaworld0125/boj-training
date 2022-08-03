#include <cmath>
#include <string>
#include <cstring>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

#define BEAM 0
#define ROOF 1
int N;

// map[y][x]에 설치하려는 구조물이 설치 가능한지 확인하고 처리하는 함수
bool installCheck(int y, int x, int type, vector<vector<vector<int>>>& map) {
    if(type == BEAM) {
        if(y == 0) return true;
        if(x > 0 && map[y][x - 1][ROOF]) return true;
        if(y < N && map[y][x][ROOF]) return true;
        if(y > 0 && map[y - 1][x][BEAM]) return true;
    }
    else {
        if(y > 0 && map[y - 1][x][BEAM]) return true;
        if(x < N && y > 0 && map[y - 1][x + 1][BEAM]) return true;
        if(x > 0 && x < N && map[y][x - 1][ROOF] && map[y][x + 1][ROOF]) return true;
    }
    return false;
}

// map[y][x]의 구조물을 삭제할 수 있는지 주변 구조물을 통해 확인하고 처리하는 함수
bool deleteCheck(int y, int x, int type, vector<vector<vector<int>>>& map) {
    map[y][x][type] = 0;

    if(type == BEAM) {
        if(y < N && map[y + 1][x][BEAM] && !installCheck(y + 1, x, BEAM, map)) return false;
        if(y < N && map[y + 1][x][ROOF] && !installCheck(y + 1, x, ROOF, map)) return false;
        if(x > 0 && y < N && map[y + 1][x - 1][ROOF] && !installCheck(y + 1, x - 1, ROOF, map)) return false;
    }
    else {
        if(map[y][x][BEAM] && !installCheck(y, x, BEAM, map)) return false;
        if(x < N && map[y][x + 1][BEAM] && !installCheck(y, x + 1, BEAM, map)) return false;
        if(x > 0 && map[y][x - 1][ROOF] && !installCheck(y, x - 1, ROOF, map)) return false;
        if(x < N && map[y][x + 1][ROOF] && !installCheck(y, x + 1, ROOF, map)) return false;
    }
    return true;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    N = n;
    
    vector<vector<int>> answer;
    vector<vector<vector<int>>> map(N + 1, vector<vector<int>>(N + 1, vector<int>(2, 0)));

    for(auto orders : build_frame) {
        
        int x = orders[0];
        int y = orders[1];
        int a = orders[2];
        int b = orders[3];

        if(b == 0) {
            if(!deleteCheck(y, x, a, map)) {
                map[y][x][a] = 1;
            }
        } 
        else {
            if(installCheck(y, x, a, map)) {
                map[y][x][a] = 1;
            }
        }
    }

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {

            if(map[j][i][BEAM]) {
                answer.push_back({i, j, BEAM});
            }
            if(map[j][i][ROOF]) {
                answer.push_back({i, j, ROOF});
            }
        }
    }
 
    return answer;
}

int main() {

    vector<int> ns = {
        5, 5
    };

    vector<vector<vector<int>>> build_frames = {
        {{1, 0, 0, 1}, {1, 1, 1, 1}, {2, 1, 0, 1}, {2, 2, 1, 1}, {5, 0, 0, 1}, {5, 1, 0, 1}, {4, 2, 1, 1}, {3, 2, 1, 1}},
        {{0, 0, 0, 1}, {2, 0, 0, 1}, {4, 0, 0, 1}, {0, 1, 1, 1}, {1, 1, 1, 1}, {2, 1, 1, 1}, {3, 1, 1, 1}, {2, 0, 0, 0}, {1, 1, 1, 0}, {2, 2, 0, 1}}
    };

    for(int i = 0; i < ns.size(); i++) {
        auto answer = solution(ns[i], build_frames[i]);

        for(auto ans : answer) {
            printf("[%d, %d, %d]\n", ans[0], ans[1], ans[2]);
        }
        printf("...\n");
    }
}