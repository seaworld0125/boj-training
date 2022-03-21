#include <iostream>
#include <vector>
using namespace std;

#define endl '\n'

int N;
int arr[2001];
bool dp[2001][2001];

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    int i, j;

    cin >> N;
    for(i = 1; i <= N; i++) cin >> arr[i];

    int start, end;
    for(i = 1; i <= N; i++) {
        for(j = 1; j + i - 1 <= N; j++) {
            start = j;
            end = j + i - 1;
            
            if(start == end) dp[start][end] = true;
            else if(start == end - 1) {
                dp[start][end] = (arr[start] == arr[end]);
            }
            else if(arr[start] == arr[end]) {
                dp[start][end] = dp[start + 1][end - 1];
            }
            else {
                dp[start][end] = false;
            }
        }
    }
    int M, S, E;
    cin >> M;
    for(i = 0; i < M; i++) {
        cin >> S >> E;
        cout << dp[S][E] << endl;
    }
}