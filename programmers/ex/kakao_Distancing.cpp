#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

int dy[] = {1, -1, 0, 0};
int dx[] = {0, 0, 1, -1};

bool check(vector<string> & room) {
    int map[5][5];
    memset(map[0], 0, sizeof(map));

    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            
            if(room[i][j] == 'P') {    
                map[i][j] -= 1;
                if(map[i][j] <= -2) return false;
                for(int k = 0; k < 4; k++) {
                    
                    int y = i + dy[k];
                    int x = j + dx[k];

                    if(y < 0 || x < 0 || y >= 5 || x >= 5 || room[y][x] == 'X') continue;
                    map[y][x] -= 1;
                    if(map[y][x] <= -2) return false;
                }                    
            }
        }
    }
    return true;
}

vector<int> solution(vector<vector<string>> places) {
    vector<int> answer;
    for(int i = 0; i < places.size(); i++) {
        answer.push_back((check(places[i]) ? 1 : 0));
    }
    return answer;
}

int main() {
    vector<vector<string>> places = {
        {"POOPO", "OOOOO", "OOOOO", "POOPO", "OOOOO"}, 
        {"POOPO", "XOOXO", "POOPO", "XPOXP", "OOOOO"}, 
        {"PXOPX", "OXOXP", "OXPOX", "OXXOP", "PXPOX"},
        {"OOOXX", "XOOOX", "OOOXX", "OXOOX", "OOOOO"}, 
        {"PXPXP", "XPXPX", "PXPXP", "XPXPX", "PXPXP"}};
 
    vector<vector<string>> places2 = {
            {"POOPO", "XOOXO", "POOPO", "XPOXP", "OOOOO"}
        };

    vector<int> ans = solution(places2);

    for(int i : ans) cout << i << " ";
}