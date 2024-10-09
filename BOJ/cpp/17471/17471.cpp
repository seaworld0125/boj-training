#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

#define INF (int)1e9
#define F first
#define S second

int N, populationSum = 0;
int population[11];
vector<int> edges[11];

void DFS(int now, bool* arr) {
    arr[now] = false;

    for(int v : edges[now]) {
        if(arr[v]) {
            DFS(v, arr);
        }
    }   
}

bool check(bool* arr) {
    int res = false;
    for(int i = 1; i <= N; i++) {
        res |= arr[i];
    }
    return res;
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> N;

    for(int i = 1; i <= N; i++) {
        cin >> population[i];
        populationSum += population[i];
    }

    int count, b;
    for(int a = 1; a <= N; a++) {
        cin >> count;

        for(int i = 0; i < count; i++) {
            cin >> b; 
            edges[a].emplace_back(b);
        }
    }

    int ans = INF;
    
    for(int i = 1; i < (1 << N) / 2; i++) {
        int aSum = 0,
            aStart,
            bStart;
        bool aArr[11] = {0},
             bArr[11] = {0};

    	for(int j = 0; j < N; j++) {
        	if(i & (1 << j)) {
            	aSum += population[j + 1];
                aArr[j + 1] = true;
                aStart = j + 1;
            }
        } 
        if(ans <= abs(populationSum - 2 * aSum)) continue;

        for(int j = 0; j < N; j++) {
        	if(~i & (1 << j)) {
                bArr[j + 1] = true;
                bStart = j + 1;
            }
        } 
        DFS(aStart, aArr);
        DFS(bStart, bArr);
        if(check(aArr) || check(bArr)) continue; 
        
        ans = abs(populationSum - 2 * aSum);
    }
    cout << (ans == INF ? -1 : ans);
}