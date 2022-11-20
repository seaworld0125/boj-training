#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define INF (int)1e9
#define MAX 151

int dist[MAX][MAX]; // [alp][cop] 까지 최단 비용
int targetAlp, targetCop; // 목표치

struct Data {
    int alp;
    int cop;
    int cost;

    Data(int alp, int cop, int cost): alp(alp), cop(cop), cost(cost) {}

    bool operator<(const Data &d) const {
        return cost < d.cost;
    }
};

void dijkstra(int alp, int cop, vector<vector<int>> &problems) {

    priority_queue<Data> pq;
    pq.emplace(alp, cop, 0);
    dist[alp][cop] = 0;

    while(!pq.empty()) {

        auto d = pq.top();
        pq.pop();

        if(d.alp >= targetAlp && d.cop >= targetCop) continue;
        if(dist[d.alp][d.cop] < d.cost) continue;

        for(auto &p : problems) {

            if(d.alp < p[0] || d.cop < p[1] || (p[2] == 0 && p[3] == 0)) continue;
                
            int nAlp = d.alp + p[2];
            int nCop = d.cop + p[3];
            int nCost = d.cost + p[4];

            /*
                최댓값을 넘어가는 경우 이를 최댓값으로 조정함
                그렇지 않으면 넓은 범위의 dist 공간을 할당해야 하는데, 이것은 비효율적이며 적절한 상한을 설정해주기 어렵다.
                이런식으로 직접 조정해주더라도 nCost에는 영향이 없음을 알 수 있다.
                즉, dist[alp 최댓값][cop 최댓값]에 값이 계속해서 갱신 될 수 있다. 
            */
            if(nAlp > targetAlp) nAlp = targetAlp; 
            if(nCop > targetCop) nCop = targetCop;

            if(dist[nAlp][nCop] > nCost) {
                dist[nAlp][nCop] = nCost;
                pq.emplace(nAlp, nCop, nCost);
            }
        }
    }
}

void init(int &alp, int &cop, vector<vector<int>> &problems) {

    targetAlp = alp;
    targetCop = cop;

    for(auto &p : problems) {
        targetAlp = max(targetAlp, p[0]);
        targetCop = max(targetCop, p[1]);
    }

    problems.push_back({0, 0, 1, 0, 1});
    problems.push_back({0, 0, 0, 1, 1});

    fill_n(dist[0], MAX * MAX, INF);
}

int solution(int alp, int cop, vector<vector<int>> problems) {

    init(alp, cop, problems);
    dijkstra(alp, cop, problems);

    return dist[targetAlp][targetCop];
}