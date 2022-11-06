#include <string>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

#define Y first
#define X second
#define MAX_RANGE 105

bool map[MAX_RANGE][MAX_RANGE];

int dy[] = {1, -1, 0, 0};
int dx[] = {0, 0, 1, -1};

int solution(vector<vector<int>> rectangle, int characterX, int characterY, int itemX, int itemY) {
    memset(map, 0, sizeof(map));

    characterY *= 2;
    characterX *= 2;
    itemY *= 2;
    itemX *= 2;

    for(auto &r : rectangle) { // 사각형 칠하기
        for(int i = r[1] * 2; i <= r[3] * 2; i++) {
            for(int j = r[0] * 2; j <= r[2] * 2; j++) {
                map[i][j] = true;
            }
        }
    }
    for(auto &r : rectangle) { // 사각형 내부 지우기
        for(int i = r[1] * 2 + 1; i < r[3] * 2; i++) {
            for(int j = r[0] * 2 + 1; j < r[2] * 2; j++) {
                map[i][j] = false;
            }
        }
    }

    queue<pair<int, int>> visit;
    visit.emplace(characterY, characterX);
    map[characterY][characterX] = false;

    int dist = 0;

    while(!visit.empty()) {

        int size = visit.size();
        for(int i = 0; i < size; i++) {

            auto now = visit.front();
            visit.pop();

            if(now.Y == itemY && now.X == itemX) {
                return dist/2;
            }

            for(int j = 0; j < 4; j++) {
                int y = now.Y + dy[j];
                int x = now.X + dx[j];

                if(y < 0 || x < 0 || y >= MAX_RANGE || x >= MAX_RANGE || !map[y][x]) continue;

                map[y][x] = false;
                visit.emplace(y, x);
            }
        }
        dist++;
    }
}