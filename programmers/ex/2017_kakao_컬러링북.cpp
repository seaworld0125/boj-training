#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};
int M, N, areaSize;

void dfs(vector<vector<bool>>& visited, vector<vector<int>>& picture, const int& target, int y, int x) {

    visited[y][x] = true;
    areaSize++;
    int ny, nx;

    for(int i = 0; i < 4; i++) {

        ny = y + dy[i];
        nx = x + dx[i];

        if(ny < 0 || nx < 0 || ny >= M || nx >= N) continue;

        if(!visited[ny][nx] && picture[ny][nx] == target) {

            dfs(visited, picture, target, ny, nx);
        }
    }
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
    M = m, N = n;
    int number_of_area = 0;
    int max_size_of_one_area = 0;
    vector<vector<bool>> visited(m, vector<bool>(n, 0));

    for(int i = 0; i < m; i++) {

        for(int j = 0; j < n; j++) {

            if(!visited[i][j] && picture[i][j] > 0) {
                
                number_of_area++;
                areaSize = 0;
                dfs(visited, picture, picture[i][j], i, j);
                max_size_of_one_area = max(max_size_of_one_area, areaSize);
            }
        }
    }

    return {number_of_area, max_size_of_one_area};
}