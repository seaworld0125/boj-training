#include <iostream>
#include <queue>
using namespace std;

#define INF (int)1e9
#define MAX 200002

int N, K;
int visited[MAX];
queue<int> visit;

inline bool checkRange(int v) {
    return v < 0 || v >= MAX || visited[v] != INF;
}

int main() {
    cin >> N >> K;
    
    visit.emplace(N);
    
    fill_n(visited, MAX, INF);
    visited[N] = 0;

    while(!visit.empty()) {
        int now = visit.front();
        visit.pop();

        int next = now + 1;
        if(!checkRange(next)) {
            visit.emplace(next);
            visited[next] = min(visited[now] + 1, visited[next]);
        }
        next = now - 1;
        if(!checkRange(next)) {
            visit.emplace(next);
            visited[next] = min(visited[now] + 1, visited[next]);
        }
        next = now * 2;
        if(!checkRange(next)) {
            visit.emplace(next);
            visited[next] = min(visited[now] + 1, visited[next]);
        }
    }
    cout << visited[K];
}