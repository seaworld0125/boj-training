#include <iostream>
#include <bitset>
#include <algorithm>
using namespace std;

#define INF (int)1e9

int N, 
    P, 
    initialStatus = 0, 
    initialCount = 0,
    ans = INF,
    map[16][16], 
    dp[1 << 16];

void DFS(int status, int count) {          // status는 고친 지점 표시, count는 고친 개수
    if(count >= P) return;

    int nextStatus, iBit;
    for(int i = 0; i < N; i++) {           // 고쳐지지 않은 지점을 고른다
        iBit = (1 << i);                   
        if(iBit & status) continue;        // 이미 고쳐진 상태                   
        nextStatus = iBit | status;        
        
        for(int j = 0; j < N; j++) {       // 어떤 발전소를 통해서 고칠 것인지
            if(i == j) continue;           // 스스로 고칠 수 없음
            
            if((1 << j) & status) { // j가 고쳐져 있는 상태의 발전소라면 사용할 수 있음
                if(dp[nextStatus] > dp[status] + map[j][i]) { // 만약 지금 발전소를 통해서 고쳤을 때 더 저렴하면 갱신
                    dp[nextStatus] = dp[status] + map[j][i];
                    
                    if(count + 1 == P) {
                        ans = min(ans, dp[nextStatus]);
                    }
                    DFS(nextStatus, count + 1);
                }
            }
        }
    }
}
int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }
    char tmp;
    for(int i = 0; i < N; i++) {
        cin >> tmp;
        
        if(tmp == 'Y') {
            initialStatus |= (1 << i); 
            initialCount++;
        }
    }   
    cin >> P;

    fill_n(dp, (1 << 16), INF); // dp초기화
    dp[initialStatus] = 0; // 시작 상태 dp 초기화

    if(initialCount >= P) cout << 0; // 더 고칠 필요가 없음
    else if(initialCount == 0) cout << -1; // 살아있는 발전소가 없음 // 불가능 
    else { // 고칠 수 있음
        DFS(initialStatus, initialCount);
        cout << ans;
    }
}