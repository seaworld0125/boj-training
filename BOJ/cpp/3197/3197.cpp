#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int R, C;
char map[1501][1501];
vector<pair<int, int>> icePos;
vector<pair<int, int>> swanPos;
queue<pair<int, int>> meltPos;
queue<pair<int, int>> movePos;
bool visited[1501][1501];

int dy[] = {0, 0, -1, 1};
int dx[] = {-1, 1, 0, 0};

bool checkRange(int y, int x) {
    return y < 0 || x < 0 || y >= R || x >= C;
}

bool infiniteSwanMove() {
    int ny, nx, y, x;
    while(1) {
        bool cantPop = true;
        int size = movePos.size();
        // cout << "size {" << size << "}\n";  
        for(int i = 0; i < size; i++) {
            ny = movePos.front().first;
            nx = movePos.front().second;
            // cout << "now[" << ny << ", " << nx << "]\n"; 

            bool canMove = false;
            for(int j = 0; j < 4; j++) {
                y = ny + dy[j];
                x = nx + dx[j];

                if(visited[y][x] || checkRange(y, x)) continue;

                if(map[y][x] == '.') {
                    // cout << "\tpush(" << y << ", " << x << ")\n";

                    movePos.emplace(y, x);
                    visited[y][x] = true;
                    canMove = true;
                }
                else if(map[y][x] == 'L') return true;
            }
            if(canMove) {
                movePos.pop();
                cantPop = false;
            }
            else {
                movePos.pop();
                movePos.emplace(ny, nx);
            }
        } 
        // cout << "-- ** --\n";
        if(cantPop) {
            return false;
        }
    }
}

void input() {
    cin >> R >> C; 

    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cin >> map[i][j];

            if(map[i][j] == 'X') icePos.emplace_back(i, j);
            else if(map[i][j] == 'L') swanPos.emplace_back(i, j);
        }
    }
}

void printMap() {
    cout << "_________________________________________\n";
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cout << map[i][j];
        }cout << endl;
    }
}

void printQueue() {
    int size = movePos.size();
    for(int i = 0; i < size; i++) {
        cout << "(" << movePos.front().first << ", " 
        << movePos.front().second << ")\n";
        auto data = movePos.front();
        movePos.pop();
        movePos.push(data);
    }
}

int main() {
    input();

    int ny, nx, y, x;
    for(int i = 0; i < icePos.size(); i++) {
        ny = icePos[i].first;
        nx = icePos[i].second;
        for(int j = 0; j < 4; j++) {
            y = ny + dy[j];
            x = nx + dx[j];

            if(checkRange(y, x)) continue;

            if(map[y][x] == '.' || map[y][x] == 'L') {
                meltPos.emplace(ny, nx);
                map[ny][nx] = 'O';
                break;
            }
        }
    }

    // printMap();

    fill_n(visited[0], 1501 * 1501, false);
    movePos.emplace(swanPos[0].first, swanPos[0].second);
    visited[swanPos[0].first][swanPos[0].second] = true;

    if(infiniteSwanMove()) {
        cout << 0;
        return 0;
    }

    int ans = 0;
    while(1) {

        ans++;
        int size = meltPos.size();
        for(int i = 0; i < size; i++) {
            ny = meltPos.front().first;
            nx = meltPos.front().second;
            meltPos.pop();

            for(int j = 0; j < 4; j++) {
                y = ny + dy[j];
                x = nx + dx[j];

                if(checkRange(y, x)) continue;

                if(map[y][x] == 'X') {
                    meltPos.emplace(y, x);
                    map[y][x] = 'O';
                }
            }
            map[ny][nx] = '.';
        }
        // printMap();
        // printQueue();
        if(infiniteSwanMove()) {
            cout << ans;
            return 0;
        }
    }
}