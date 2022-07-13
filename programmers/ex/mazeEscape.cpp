#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

#define INF (int)1e9

struct Road {
    int dest;
    int cost;
    Road(int d, int c) : dest(d), cost(c) {}
};
vector<Road> roadInfo[1001];
vector<Road> reverseRoadInfo[1001];

int END;
int answer = (int)1e9;

bool trapList[1001] = {0};
bool trapState[1001] = {0};

void recursive(int now, int dist) {
    if(dist > answer) return;
    if(now == END) {
        answer = min(answer, dist);
    }
    else {
        if(trapList[now]) { // 현재 트랩이라면
            trapState[now] = !trapState[now]; // 트랩 상태 반전 

            if(trapState[now]) { // 뒤집힌 방향 (트랩 -> 목적지)
                int size = reverseRoadInfo[now].size();
                for(int i = 0; i < size; i++) {
                    recursive(reverseRoadInfo[now][i].dest, dist + reverseRoadInfo[now][i].cost);    
                }
            }
            else { // 원래 방향 (트랩 -> 목적지)
                int size = roadInfo[now].size();
                for(int i = 0; i < size; i++) {
                    recursive(roadInfo[now][i].dest, dist + roadInfo[now][i].cost);    
                }
            }
            trapState[now] = !trapState[now]; // 트랩 상태 돌려놓기 
        }
        else { // 트랩이 아니라면
            int size = roadInfo[now].size();
            for(int i = 0; i < size; i++) {
                recursive(roadInfo[now][i].dest, dist + roadInfo[now][i].cost);
            }
        }
    }
}

int solution(int n, int start, int end, vector<vector<int>> roads, vector<int> traps) {
    END = end;
    
    for(int i = 0; i < traps.size(); i++) {
        trapList[traps[i]] = true;
    }

    int a, b, c;
    for(auto road : roads) {
        a = road[0],
        b = road[1],
        c = road[2];
        roadInfo[a].emplace_back(b, c);

        if(trapList[b]) { // 도착지점이 트랩인 경우
            reverseRoadInfo[b].emplace_back(a, c); // 트랩 -> a 경로 추가
        }
    }
    recursive(start, 0);
    return answer;
}