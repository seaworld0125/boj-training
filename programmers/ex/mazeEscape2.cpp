#include <string>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int dp[1001][1 << 10];

vector<pair<int, int>> roadList[1001];
vector<pair<int, int>> reverseRoadList[1001];
bool trapList[1001];

int solution(int n, int start, int end, vector<vector<int>> roads, vector<int> traps) {
    int answer = 0;

    for(auto& road : roads) {
        roadList[road[0]].emplace_back(road[1], road[2]);
        reverseRoadList[road[1]].emplace_back(road[0], road[2]);
    }
    for(auto& trap : traps) {
        trapList[trap] = true;
    }

    memset(dp[0], 0, sizeof(dp));

    queue<pair<int, int>> q; // now, state
    q.emplace(start, 0);

    dp[start][0] = 0;

    while(!q.empty()) {
        int now = q.front().first;
        int state = q.front().second;
        int size = roads[now].size();
        q.pop();

        if(now == end) {
            answer = min(answer, dp[now][state]);
            continue;
        }

        bool isTrap = false;

        if(trapList[now]) {
            if((state >> now) & 1) {
                isTrap = true;
            }
        }

        for(int i = 0; i < size; i++) {
            int cost = roadList[now][i].second;
            int node;

            if(isTrap) {
                node = reverseRoadList[now][i].first;
            }
            else {
                node = roadList[now][i].first;
            }
            int newState = 

            dp[node][newState] += cost;
        }
    }

    return answer;
}