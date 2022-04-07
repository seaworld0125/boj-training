#include <iostream>
#include <vector>
using namespace std;

int root = 1;
int sequence = 1;
int visitSeq[8] = {0};
bool breakPoint[8] = {0};
vector<int> edges[8];

int findBreakPoint(int now) {
    // 방문 순서를 기록하고 sequence를 증가시킨다.
    int fastestOne = sequence;
    visitSeq[now] = sequence++;

    // 루트 노드를 위한 childCount
    int childCount = 0;

    // now 노드와 연결된 간선을 모두 탐색
    for(int next : edges[now]) {
        
        // 방문했던 노드라면 방문 순서를 비교해서 더 작은 순서로 갱신
        if(visitSeq[next]) {
            fastestOne = min(fastestOne, visitSeq[next]);
            continue;
        }
        
        // 자식(트리) 수 증가
        childCount++;

        // 방문한 적 없으니 함수 호출(탐색)
        int minSeq = findBreakPoint(next);

        // 자식 노드들이 방문할 수 있는 노드 중 가장 빠른 순서가 현재 노드 방문 순서보다 낮다면 단절점이므로
        if(now != root && visitSeq[now] <= minSeq) {
            breakPoint[now] = true;
        }

        // 더 작은 방문 순서로 갱신
        fastestOne = min(fastestOne, minSeq);
    }
    // 루트 노드인데 자식(트리)가 두개 이상이라면
    if(now == root && childCount >= 2) {
        breakPoint[now] = true;
    } 
    
    return fastestOne;
}

int main() {
    
    // 간선 설정
    edges[1].emplace_back(2);
    edges[1].emplace_back(5);
    
    edges[2].emplace_back(3);
    edges[2].emplace_back(4);
    
    edges[5].emplace_back(6);
    edges[5].emplace_back(7);
    

    findBreakPoint(1);

    for(int i = 1; i < 8; i++) {
        if(breakPoint[i])
            cout << i << " is breakPoint\n";
        else
            cout << i << " is not breakPoint\n"; 
    }   
}