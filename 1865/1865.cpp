#include <iostream>
#include <vector>

using namespace std;

#define INF (int)1e9

struct Edge {
    int start;
    int end;
    int cost;

    Edge(int s, int e, int c): start(s), end(e), cost(c) {}
};

int TC, N, M, W; 

bool BF(vector<Edge> & edges, int * dist) {
    int size = edges.size();

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < size; j++) {
            if(dist[edges[j].end] > dist[edges[j].start] + edges[j].cost) {
                dist[edges[j].end] = dist[edges[j].start] + edges[j].cost;

                if(i == N - 1) return true;
            }
        }
    }
    for(int i = 0; i < size; i++) {
        if(dist[edges[i].end] > dist[edges[i].start] + edges[i].cost) {
            return true;
        }
    }
    return false;
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> TC;

    for(int i = 0; i < TC; i++) {
        cin >> N >> M >> W;

        vector<Edge> edges;
        int dist[501] = {0};

        int S, E, T;
        for(int j = 0; j < M; j++) {
            cin >> S >> E >> T;
            edges.emplace_back(S, E, T);
            edges.emplace_back(E, S, T);
        }
        for(int j = 0; j < W; j++) {
            cin >> S >> E >> T;
            edges.emplace_back(S, E, -T);
        }
        cout << (BF(edges, dist) ? "YES\n" : "NO\n");
    }
}