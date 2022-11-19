#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

#define INF (int)1e9

char idx[12] = {'1','2','3','4','5','6','7','8','9','*','0','#'};
unordered_map<char, int> idxMap;

char pad[4][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}};
unordered_map<char, pair<int, int>> padMap;

int dy1[] = {-1, 1, 0, 0}; 
int dx1[] = {0, 0, -1, 1};
int dy2[] = {-1, 1, 1, -1};
int dx2[] = {1, 1, -1, -1};

vector<pair<int, int>> edges[12]; // dist[idx] = {n, c} -> idx 에서 n 까지의 거리: c

int dist[12][12];
 
inline bool oor(int &y, int &x) {
    return y < 0 || x < 0 || y >= 4 || x >= 3;
}

void _init() {
    for(int i = 0; i < 12; i++) {
        idxMap[idx[i]] = i;
    }
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 3; j++) {
            padMap[pad[i][j]] = {i, j};
        }
    }
    fill_n(dist[0], 12 * 12, INF);
}

void addEdges() {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 3; j++) {

            auto nIdx = idxMap[pad[i][j]];
            auto pos = padMap[pad[i][j]];
            int y, x;

            for(int k = 0; k < 4; k++) {
                y = pos.first + dy1[k];
                x = pos.second + dx1[k];

                if(oor(y, x)) continue;

                edges[nIdx].emplace_back(idxMap[pad[y][x]], 2);
            }
            for(int k = 0; k < 4; k++) {
                y = pos.first + dy2[k];
                x = pos.second + dx2[k];

                if(oor(y, x)) continue;

                edges[nIdx].emplace_back(idxMap[pad[y][x]], 3);
            }
        }
    }
}

void calcDist() {

    for(int i = 0; i < 12; i++) {
        for(auto e : edges[i]) {
            dist[i][e.first] = e.second;
        }
    }

    for(int mid = 0; mid < 12; mid++) {
        for(int i = 0; i < 12; i++) {
            for(int j = 0; j < 12; j++) {

                if(i == j) dist[i][j] = 1;

                if(dist[i][j] > dist[i][mid] + dist[mid][j]) {
                    dist[i][j] = dist[i][mid] + dist[mid][j];
                }
            }
        }
    }

    printf("   ");
    for(int i = 0; i < 12; i++ ) {
        printf("%c ", idx[i]);
    }printf("\n   ");
    for(int i = 0; i < 12; i++ ) {
        printf("_ ", idx[i]);
    }printf("\n");

    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 12; j++) {
            if(j == 0) {
                printf("%c| ", idx[i]);
            }
            printf("%d ", dist[i][j] == INF ? 0 : dist[i][j]);        
        }printf("\n");
    }
}

int solve(string &numbers, int i, int a, int b, int cost) {

    if(i == numbers.length()) {
        return cost;
    }

    int nIdx = idxMap[numbers[i]];

    int res1 = solve(numbers, i + 1, nIdx, b, cost + dist[a][nIdx]);
    int res2 = solve(numbers, i + 1, a, nIdx, cost + dist[b][nIdx]);

    return min(res1, res2);
}

int solution(string numbers) {

    _init();
    addEdges();
    calcDist();
    return solve(numbers, 0, 3, 5, 0);
}

/*

채점을 시작합니다.
정확성  테스트
                    테스트 1 〉	통과 (0.02ms, 3.68MB)
                    테스트 2 〉	통과 (0.02ms, 4.15MB)
                    테스트 3 〉	통과 (0.02ms, 4.16MB)
                    테스트 4 〉	통과 (0.03ms, 3.69MB)
                    테스트 5 〉	통과 (0.03ms, 3.59MB)
                    테스트 6 〉	실패 (0.02ms, 4.22MB)
                    테스트 7 〉	실패 (0.02ms, 4.21MB)
                    테스트 8 〉	실패 (0.02ms, 4.07MB)
                    테스트 9 〉	실패 (0.02ms, 3.64MB)
                    테스트 10 〉	실패 (0.02ms, 4.02MB)
                    테스트 11 〉	통과 (14.25ms, 4.23MB)
                    테스트 12 〉	통과 (16.09ms, 4.21MB)
                    테스트 13 〉	통과 (14.88ms, 3.59MB)
                    테스트 14 〉	통과 (14.08ms, 4.21MB)
                    테스트 15 〉	통과 (15.43ms, 4.03MB)
                    테스트 16 〉	실패 (시간 초과)
                    테스트 17 〉	실패 (시간 초과)
                    테스트 18 〉	실패 (시간 초과)
                    테스트 19 〉	실패 (시간 초과)
                    테스트 20 〉	실패 (시간 초과)
채점 결과
정확성: 50.0
합계: 50.0 / 100.0

Review
------
일단 재귀로 접근해야하는 것은 맞다

문제는 두 손가락 중에 어떤 것으로 눌러야 전체적인 최적값이 나오는지는 명확하지가 않다.

그럼 일단 다 눌러보자.

그래 다 눌렀다.

그럼 2 ^ 100,000 만큼 재귀 탐색이 수행되어야 한다. ㄷㄷ 



*/