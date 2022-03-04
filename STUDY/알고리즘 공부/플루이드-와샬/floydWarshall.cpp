#include <iostream>
using namespace std;

#define INF (int)1e9

int arr[5][5] = {
    {0, 1, 1, INF, INF},
    {INF, 0, INF, INF, 1},
    {3, INF, 0, INF, 2},
    {INF, 3, INF, 0, 1},
    {INF, INF, INF, 1, 0}
};

int main() {
    for(int k = 0; k < 5; k++) {
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 5; j++) {
                if(arr[i][j] > arr[i][k] + arr[k][j]) {
                    arr[i][j] = arr[i][k] + arr[k][j];
                }
            }
        }
    }

    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            if(arr[i][j] == INF) cout << "- ";
            else cout << arr[i][j] << ' ';
        }cout << endl;
    }
}