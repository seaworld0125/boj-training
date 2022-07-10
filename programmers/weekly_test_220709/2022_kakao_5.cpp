#include <iostream>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <bitset>
#include <deque>
#include <map>
#include <cmath>
using namespace std;

#define pii pair<int, int>
#define F first
#define S second

#define endl '\n'

/*
    이 문제는 노드의 방문 순서가 중요하지 않다.
    모든 노드는 현재 방문 상태에 따라서 이후에 방문할 수 있는 노드가 되기도 하고 방문할 수 없는 노드가 되기도 한다.
    모든 상태(경우의 수)를 효율적으로 고려하는 비트마스킹을 이용한 DFS 또는 BFS로 접근하여 풀 수 있다.
*/

vector<int> tree[17];
bool visited[(1 << 17)] = {0};

struct Data {
    int wolf;
    int sheep;
    int status;

    Data(int _wolf, int _sheep, int _status):wolf(_wolf), sheep(_sheep), status(_status) {}
};

void solve(const vector<int>& info, int& answer, Data data) {
    // 현재 status 방문 체크
    visited[data.status] = true;

    int infoSize = info.size();
    // 현재 방문한 노드 확인
    for(int i = 0; i < infoSize; i++) {
        if(data.status & (1 << i)) {
            // i번째 노드에서 고려할 수 있는 경우는 자식 노드로의 이동이다
            for(int child : tree[i]) {

                // 새로운 상태
                int newStatus = data.status | (1 << child);

                // 이미 newStatus를 확인해봤다면
                if(visited[newStatus]) continue;

                // 늑대라면
                if(info[child]) {
                    if(data.sheep > data.wolf + 1) {
                        solve(info, answer, Data(data.wolf + 1, data.sheep, newStatus));
                    }
                }
                // 양이라면
                else {  
                    answer = max(answer, data.sheep + 1);
                    solve(info, answer, Data(data.wolf, data.sheep + 1, newStatus));
                }
            }
        }
    }
}

int solution(vector<int> info, vector<vector<int>> edges) {

    // 트리 구성
    for(vector<int>& edge : edges) {
        tree[edge[0]].emplace_back(edge[1]);
    }

    int answer = 1;
    solve(info, answer, Data(0, 1, (1 << 0)));

    return answer;
}

int main() {
    vector<vector<vector<int>>> edgeList = {
        // {{0, 1}, {1, 2}, {1, 4}, {0, 8}, {8, 7}, {9, 10}, {9, 11}, {4, 3}, {6, 5}, {4, 6}, {8, 9}},
        {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}, {3, 7}, {4, 8}, {6, 9}, {9, 10}}
    };

    vector<vector<int>> infoList = {
        // {0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1},
        {0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0}
    };

    for(int i = 0; i < edgeList.size(); i++) {

        for(int i = 0; i < 17; i++) tree[i].clear();
        memset(visited, 0, sizeof(visited));

        cout << "==============new case==============\n";
        cout << "ans = " << solution(infoList[i], edgeList[i]) << endl;
    }
}