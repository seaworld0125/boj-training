#include <iostream>
#include <vector>
#include <algorithm>
#define INF (int)1e9
using namespace std;


int n, m;
int edgeArr[101][101];

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i == j) edgeArr[i][j] = 0;
            else edgeArr[i][j] = INF;
        }
    }

    int start, end, cost;
    for(int i = 0; i < m; i++) {
        cin >> start >> end >> cost;
        edgeArr[start - 1][end - 1] = min(edgeArr[start - 1][end - 1], cost);
    }

    for(int k = 0; k < n; k++) 
        for(int i = 0; i < n; i++) 
            for(int j = 0; j < n; j++) 
                if(edgeArr[i][j] > edgeArr[i][k] + edgeArr[k][j])
                    edgeArr[i][j] = edgeArr[i][k] + edgeArr[k][j];

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << (edgeArr[i][j] == INF ? 0 : edgeArr[i][j]) << ' ';
        }cout << endl;
    }
}