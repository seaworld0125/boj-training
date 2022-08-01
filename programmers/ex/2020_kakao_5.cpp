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

#define pii pair<int, int>
#define F first
#define S second
#define ll long long
#define INF (int)1e9

int MAP_SIZE;

// pii pos의 좌표의 범위를 확인한느 함수
bool outOfRange(int y, int x) {
    if(y < 0 || x < 0 || y >= MAP_SIZE || x >= MAP_SIZE) return true;
    return false;
}

// map[y][x] 의 구조물이 안전한지 확인하는 함수
bool safeCheck(int y, int x, vector<vector<int>>& map) { 
    if(outOfRange(y, x) || map[y][x] == -1) return true;

    if(map[y][x] == 0) {
        if(!outOfRange(y, x - 1) && map[y][x - 1] == 1)
            return true;
        if(!outOfRange(y - 1, x) && map[y - 1][x] == 0)
            return true;
        if(y == 0)
            return true;
    }
    else {
        if(!outOfRange(y - 1, x) && map[y - 1][x] == 0) 
            return true;
        if(!outOfRange(y - 1, x + 1) && map[y - 1][x + 1] == 0) 
            return true;
        if((!outOfRange(y, x - 1) && !outOfRange(y, x + 1)) && (map[y][x - 1] == 1 && map[y][x + 1] == 1))
            return true;
    }
    return false;
}

// map[y][x]의 구조물을 삭제할 수 있는지 주변 구조물을 통해 확인하고 처리하는 함수
void deleteSafeCheckAroundStructure(int y, int x, vector<vector<int>>& map) {
    if(map[y][x] == 0) {
        map[y][x] = -1;
        
        if(!safeCheck(y + 1, x, map) || !safeCheck(y + 1, x - 1, map)) {
            map[y][x] = 0;
        }
    }
    else {
        map[y][x] = -1;

        if(!safeCheck(y, x - 1, map) || !safeCheck(y, x + 1, map)) {
            map[y][x] = 1;
        }
    }
}

// map[y][x]에 설치하려는 구조물이 설치 가능한지 확인하고 처리하는 함수
void installCheck(int y, int x, vector<vector<int>>& map) {
    if(map[y][x] == 0) {
        map[y][x] = 0;
    }
    else {

    }
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    MAP_SIZE = n;
    
    vector<vector<int>> answer;
    vector<vector<int>> map(MAP_SIZE, vector<int>(MAP_SIZE, -1));

    for(auto orders : build_frame) {
        
        int x = orders[0];
        int y = orders[1];
        int a = orders[2];
        int b = orders[3];

        if(a == 0) { // 기둥
            if(b == 0) { // 삭제

            } 
            else { // 설치
                if(y == 0) {
                    map[y][x] = a;
                }
                else if(y > 0) {
                    if(map[y - 1][x] == 0 || map[y - 1][x] == 1 || map[y - 1][x - 1] == 1) {
                        map[y][x] = a;
                    }
                }
            }
        }
        else {

        }
    }
 
    return answer;
}

int main() {

}