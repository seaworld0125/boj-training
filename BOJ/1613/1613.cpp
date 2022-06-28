#include <iostream>
#include <vector>
using namespace std;

#define INF (int)1e9
#define endl '\n'

int distMap[401][401];

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    int n, k;
    cin >> n >> k;

    // 거리 맵 초기화
    fill_n(distMap[0], 401 * 401, INF);
    for(int i = 1; i <= n; i++) {
        distMap[i][i] = 0;
    }

    int a, b;
    for(int i = 0; i < k; i++) {
        cin >> a >> b;

        // 순서가 주어진다면 거리는 무조건 1로 설정
        distMap[a][b] = 1;
    }

    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(i == j) continue;

                if(distMap[i][j] > distMap[i][k] + distMap[k][j]) {
                    distMap[i][j] = distMap[i][k] + distMap[k][j];
                }
            }
        }
    }

    int s;
    cin >> s;

    int distA, distB;
    for(int i = 0; i < s; i++) {
        cin >> a >> b;

        distA = distMap[a][b];
        distB = distMap[b][a];

        if(distA == INF && distB == INF) cout << 0 << endl;
        else if(distA == INF) cout << 1 << endl;
        else if(distB == INF) cout << -1 << endl;
    }
}