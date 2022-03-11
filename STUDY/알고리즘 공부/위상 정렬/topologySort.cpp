#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAX 10

int n = 5;
int inDegree[MAX];
vector<int> edges[MAX];

void topologySort() {
    queue<int> vq;

    for(int i = 0; i < MAX; i++)
        if(inDegree[i] == 0)
            vq.emplace(i);

    for(int i = 0; i < n; i++) {
        if(vq.empty()) {
            cout << "그래프 내에 사이클이 존재합니다.\n";
            return;
        }

        // 큐에서 노드를 꺼낸다
        int now = vq.front();
        vq.pop();
        
        // print result
        cout << now << ' ';

        // 해당 노드의 간선을 제거
        for(int j = 0; j < edges[now].size(); j++) {
            
            if(--inDegree[edges[now][j]] == 0) {
                // 진입 차수가 0이 되었다면 큐에 삽입
                vq.emplace(edges[now][j]);
            }
        }
    }
}

inline int reset(int num) {
    return (num == -1 ? 0 : num);
}

int main() {
    // initial set
    fill_n(inDegree, MAX, -1);

    inDegree[1] = 0;

    edges[1].emplace_back(3);
    inDegree[3] = reset(inDegree[3]) + 1;

    edges[3].emplace_back(4);
    inDegree[4] = reset(inDegree[4]) + 1;
    
    edges[3].emplace_back(7);
    inDegree[7] = reset(inDegree[7]) + 1;
    
    edges[4].emplace_back(6);
    inDegree[6] = reset(inDegree[6]) + 1;
    
    edges[7].emplace_back(6);
    inDegree[6] = reset(inDegree[6]) + 1;

    topologySort();
}