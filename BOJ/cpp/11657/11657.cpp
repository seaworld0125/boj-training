#include <iostream>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
using namespace std;

#define pii pair<int, int>
#define F first
#define S second
#define INF (int)1e9
#define ll long long 

#define endl '\n'

struct Edge {
    int a;
    int b;
    int c;
    Edge(int A, int B, int C): a(A), b(B), c(C) {}
};

int N, M, A, B, C; 
ll dist[501];
vector<Edge> edges; 

bool solve() {
    dist[1] = 0;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {

            if(dist[edges[j].a] == INF) continue;

            if(dist[edges[j].b] > dist[edges[j].a] + edges[j].c) {
                dist[edges[j].b] = dist[edges[j].a] + edges[j].c;

                if(i == N - 1) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    fill_n(dist, 501, INF);

    cin >> N >> M;

    for(int i = 0; i < M; i++) {
        cin >> A >> B >> C; 
        edges.emplace_back(A, B, C);
    }

    if(solve()) {
        for(int i = 2; i <= N; i++) {
            cout << (dist[i] == INF ? -1 : dist[i]) << endl;
        }
    }
    else cout << -1;
}