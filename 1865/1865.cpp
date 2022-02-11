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

int dist[501];

int TC, N, M, W; 

bool BF(vector<Edge> & edges) {
    int now, dest, cost;
    int size = edges.size();

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < size; j++) {
            now = edges[j].start;
            dest = edges[j].end;
            cost = edges[j].cost;
            
            if(dist[now] != INF && dist[dest] > dist[now] + cost) {
                dist[dest] = dist[now] + cost;

                if(i == N - 1) return true;
            }
        }
    }
    for(int i = 0; i < size; i++) {
        now = edges[i].start;
        dest = edges[i].end;
        cost = edges[i].cost;
        
        if(dist[now] != INF && dist[dest] > dist[now] + cost) {
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
        fill_n(dist, N + 1, 0);

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

        bool ans = BF(edges);

        cout << (ans ? "YES\n" : "NO\n");
    }
}