#include <queue>
#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define INF (int)1e9
#define pii pair<int, int>
#define F first
#define S second

int dist[50001];
vector<pair<int, int>> edges[50001];

void recursive(vector<vector<int>>& paths, vector<int>& gates) {
    fill_n(dist, sizeof(dist), INF);
    priority_queue<pii> pq;

    for(auto g : gates) {
        dist[g] = 0;
        pq.emplace(0, g);
    }

    while(!pq.empty()) {
        int cost = pq.top().F;
        int cur = pq.top().S;
        pq.pop();

        for(auto next : edges[cur]) {
            int nCost = next.S;
            int nCur = next.F;

            if(dist[nCur] > max(dist[cur], nCost)) {
                dist[nCur] = max(dist[cur], nCost);
                pq.emplace(nCost, nCur);
            }
        }
    }
}

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    for(auto v : paths) {
        edges[v[0]].emplace_back(v[1], v[2]);
        edges[v[1]].emplace_back(v[0], v[2]);
    }
    recursive(paths, gates);

    int minSummit = INF, minIntensity = INF;
    for(auto s : summits) {
        if(minIntensity > dist[s]) {
            minIntensity = dist[s];
            minSummit = s;
        }
        else if(minIntensity == dist[s]) {
            minSummit = min(minSummit, s);
        }
    }
    return {minSummit, minIntensity};
}

int main() {
    solution(6, {{1, 2, 3}, {2, 3, 5}, {2, 4, 2}, {2, 5, 4}, {3, 4, 4}, {4, 5, 3}, {4, 6, 1}, {5, 6, 1}}, {1, 3}, {5});
}