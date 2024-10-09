#include <iostream>
#include <vector>
using namespace std;

int findParent(int* parent, int now) {
    return (parent[now] == now ? now : findParent(parent, parent[now]));
}

void unionParent(int* parent, int a, int b) {
    a = findParent(parent, a);
    b = findParent(parent, b);
    if(a < b) parent[b] = a;
    else parent[a] = b;
}

bool checkParent(int* parent, vector<int> & path) {
    int parentNum = findParent(parent, path[0]);
    
    for(int i = 1; i < path.size(); i++)
        if(parentNum != findParent(parent, path[i])) return false;

    return true;
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, M;
    int map[201][201];
    int parent[201];

    cin >> N >> M;
    vector<int> path(M);

    for(int i = 1; i <= N; i++) 
        parent[i] = i;
    
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            cin >> map[i][j];
            
            if(map[i][j] && i < j) {
                unionParent(parent, i, j);
            }
        }
    }
    
    for(int i = 0; i < M; i++) 
        cin >> path[i];

    cout << (checkParent(parent, path) ? "YES" : "NO");
}