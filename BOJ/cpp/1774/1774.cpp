#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

#define pii pair<int, int>
#define F first
#define S second

int N, M;
int parent[1001];
vector<pii> pos;

struct DistData {
    double dist;
    int A;
    int B;

    DistData(double d, int a, int b):dist(d), A(a), B(b) {}
};

vector<DistData> distDataList;

int findParent(int a) {
    if(parent[a] == a) return a;
    return parent[a] = findParent(parent[a]);
}

bool checkSameParent(int a, int b) {
    return findParent(a) == findParent(b);
}

bool unionParent(int a, int b) {
    a = findParent(a);
    b = findParent(b);

    if(a == b) return false;
    else if(a < b) parent[b] = a;
    else parent[a] = b;
    return true;
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> N >> M;

    int a, b;
    for(int i = 0; i < N; i++) {
        
        cin >> a >> b;
        pos.emplace_back(a, b);
    }

    // parent 초기화
    for(int i = 0; i < N; i++) {
        parent[i] = i;
    }

    for(int i = 0; i < M; i++) {

        cin >> a >> b;
        unionParent(a - 1, b - 1);
    }

    double dist;
    for(int i = 0; i < N; i++) {
        for(int j = i + 1; j < N; j++) {

            // 만약 부모가 이미 같다면 거리를 계산하지 않음
            if(checkSameParent(i, j)) continue;

            // 거리 계산 후 정보 추가
            dist = pow((pos[i].F - pos[j].F), 2) + pow((pos[i].S - pos[j].S), 2);
            dist = sqrt(dist);

            // printf("new Data = (%f, %d, %d)\n", dist, i, j);
            distDataList.emplace_back(dist, i, j);
        }
    }

    sort(distDataList.begin(), distDataList.end(), [](DistData& a, DistData& b) {
        if(a.dist < b.dist) return true;
        else return false;
    });

    double ans = 0;
    int size = distDataList.size();
    // printf("distDataList size = %d\n", size);
    for(int i = 0; i < size; i++) {

        if(!unionParent(distDataList[i].A, distDataList[i].B)) continue;
        ans += distDataList[i].dist;
    }
    cout << fixed;
    cout.precision(2);
    cout << ans;
}