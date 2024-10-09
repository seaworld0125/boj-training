#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int T, n;
int selectList[100001];
int visited[100001];

int main() {
    cin >> T;

    while(T--) {
        cin >> n;
        int ans = n;

        for(int i = 1; i <= n; i++) {
            cin >> selectList[i];
            visited[i] = false;

            if(i == selectList[i]) {
                visited[i] = 1;
                ans--;
            }
        }
        
        for(int i = 1; i <= n; i++) {
            if(visited[i]) continue;

            vector<int> visitList;
            vector<bool> history(n + 1, 0);

            int now = i;
            while(1) {
                visitList.emplace_back(now);
                history[now] = true;

                now = selectList[now];
                
                if(visited[now]) break; // 예전 순회에서 방문했던 곳이라면 종료
                if(history[now]) { // 이번 순회에서 방문했던 곳이라면 사이클이 있다는 뜻

                    while(1) {
                        int i;
                        for(i = 0; i < visitList.size(); i++) {
                            if(visitList[i] == now) break;
                            visited[i] = 2; // 2 또는 0은 팀이 없는 멤버
                        }
                        for(; i < visitList.size(); i++) {
                            visited[i] = 1;
                            ans--;
                        }
                    }
                }
            }
        }
        cout << ans << endl;
    }
}