#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define endl '\n'

int V, E, root, orderCount = 1, ans = 0;
int visitOrder[10001] = {0};
bool breakPoint[10001] = {0};
vector<int> edges[10001];

int findBreakPoint(int now) {

    int child = 0;                  // 자식 수.. root 노드일 때만 필요함
    int minOrder = orderCount;      // 내 순서로 초기화
    visitOrder[now] = orderCount++; // 방문 순서 기록

    for(int next : edges[now]) {
        if(visitOrder[next]) {
            minOrder = min(minOrder, visitOrder[next]); // 연결된 노드 중에서 가장 작은 방문 순서로 갱신
            continue;
        }
        child++; // 자식 트리 수 증가

        int childMinOrder = findBreakPoint(next); // 자식 노드들이 접근할 수 있는 가장 빠른 방문 순서

        if(now != root && visitOrder[now] <= childMinOrder && !breakPoint[now]) { // 단절점이므로 
            breakPoint[now] = true;
            ans++;
        }
        minOrder = min(minOrder, childMinOrder);        
    }
    if(now == root && child >= 2) {
        breakPoint[now] = true;
        ans++;
    }    
    return minOrder;
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> V >> E;

    int a, b;
    for(int i = 0; i < E; i++) {
        cin >> a >> b;

        edges[a].emplace_back(b);
        edges[b].emplace_back(a);       
    }
    for(int i = 1; i <= V; i++) {
        if(visitOrder[i]) continue;

        root = i;
        findBreakPoint(i);
    }
    
    cout << ans << endl;

    for(int i = 1; i <= V; i++) {
        if(!breakPoint[i]) continue;

        cout << i << ' ';
    }
}