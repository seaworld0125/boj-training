#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAX 32010

int N, M;
int inDegree[MAX];
vector<int> edges[MAX];

void topologySort() {
    queue<int> vq;

    for(int i = 1; i <= N; i++)
        if(inDegree[i] == -1)
            vq.emplace(i);
    
    for(int i = 0; i < N; i++) {
        int now = vq.front();
        vq.pop();

        cout << now << ' ';

        for(int j = 0; j < edges[now].size(); j++) {
            if(--inDegree[edges[now][j]] == 0) {
                vq.emplace(edges[now][j]);
            }
        }
    }
}

inline int reset(int num) {
    return (num == -1 ? 0 : num);
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    fill_n(inDegree, N + 1, -1);

    int a, b;
    for(int i = 0; i < M; i++) {
        cin >> a >> b;
        edges[a].emplace_back(b);
        
        inDegree[b] = reset(inDegree[b]) + 1;
    }

    topologySort();
}