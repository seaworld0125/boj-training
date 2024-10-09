#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N;
int complex = 0;
vector<int> complexSize;

bool map[26][26];

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

void BFS(int y, int x) {
    map[y][x] = false;
    queue<pair<int, int>> q;

    int count = 0;

    q.emplace(y, x);
    while(!q.empty()) {
        auto pos = q.front();
        q.pop();
        count++;

        for(int i = 0; i < 4; i++) {
            int y_ = pos.first + dy[i];
            int x_ = pos.second + dx[i];

            if(y_ < 0 || y_ >= N || x_ < 0 || x_ >= N) continue;

            if(map[y_][x_]) {
                map[y_][x_] = false;
                q.emplace(y_, x_);
            }
        }
    }
    complex++;
    complexSize.emplace_back(count);
}

int main() {
    cin >> N;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            char c;
            cin >> c;
            map[i][j] = c - '0';
        }
    }

    for(int i = 0; i < N; i++) 
        for(int j = 0; j < N; j++)
            if(map[i][j]) 
                BFS(i, j);

    sort(complexSize.begin(), complexSize.end());

    cout << complex << '\n';
    for(int i = 0; i < complexSize.size(); i++) 
        cout << complexSize[i] << '\n';
}