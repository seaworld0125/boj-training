#include <iostream>
using namespace std;

#define INF (int)1e9

int dist[1001][1001], a, b, c;

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, M;
    cin >> N >> M;

    fill_n(dist[0], 1001 * 1001, INF);

    for(int i = 0; i < N - 1; i++) {
        cin >> a >> b >> c; 
        dist[a][b] = c; 
        dist[b][a] = c;
    }

    for(int k = 1; k <= N; k++) {
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                if(i == j) {
                    dist[i][j] = 0;
                    dist[j][i] = 0;
                    continue;
                }

                if(dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    for(int i = 0; i < M; i++) {
        cin >> a >> b; 
        cout << (dist[a][b] == INF ? dist[b][a] : dist[a][b]) << endl;
    }
}