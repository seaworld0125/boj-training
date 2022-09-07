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
vector<pii> edges[50001]; // <weight, node>

bool isGate[50001];
bool isSummit[50001];

void dijkstra(vector<int>& gates) {
    fill_n(dist, 50001, INF);
    priority_queue<pii, vector<pii>, greater<pii>> visit;
    
    for(auto g : gates) {
        visit.emplace(0, g);
        dist[g] = 0;
    }

    while(!visit.empty()) {
        auto cost = visit.top().F;
        auto pos = visit.top().S;
        visit.pop();

        for(auto next : edges[pos]) {
            auto nCost = next.F;
            auto nPos = next.S;

            if(dist[nPos] > max(dist[pos], nCost)) {
                dist[nPos] = max(dist[pos], nCost);
                visit.emplace(dist[nPos], nPos);
            }
        }
    }
}

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    for(auto g : gates) isGate[g] = true;
    for(auto s : summits) isSummit[s] = true;

    for(auto path : paths) {
        int i = path[0];
        int j = path[1];
        int w = path[2];

        if(isGate[i] || isSummit[j]) {
            edges[i].emplace_back(w, j);
        }
        else if(isGate[j] || isSummit[i]) {
            edges[j].emplace_back(w, i);
        }
        else {
            edges[i].emplace_back(w, j);
            edges[j].emplace_back(w, i);
        }
    }

    dijkstra(gates);

    int minSummit = INF, 
        minIntensity = INF;

    for(auto summit : summits) {
        if(dist[summit] == INF) continue;
        if(minIntensity > dist[summit]) {
            minIntensity = dist[summit];
            minSummit = summit;
        }
        else if(minIntensity == dist[summit] && minSummit > summit) {
            minSummit = summit;
        }
    }
    return {minSummit, minIntensity};
}

int main() {
    solution(6, {{1, 2, 3}, {2, 3, 5}, {2, 4, 2}, {2, 5, 4}, {3, 4, 4}, {4, 5, 3}, {4, 6, 1}, {5, 6, 1}}, {1, 3}, {5});
}