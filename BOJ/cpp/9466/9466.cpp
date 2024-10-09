#include <iostream>
#include <vector>
using namespace std;

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T, N, num;
    cin >> T;

    for(int i = 0; i < T; i++) {
        cin >> N;

        int ans = N;

        int edges[100001];
        fill_n(edges, N + 1, 0);
        bool hasTeam[100001];
        fill_n(hasTeam, N + 1, false);
        int visit[100001];
        fill_n(visit, N + 1, 0);

        for(int j = 1; j <= N; j++) {
            cin >> num;
            edges[j] = num;

            if(j == num) { 
                hasTeam[j] = true;
                ans--;
            }
        }
        for(int j = 1; j <= N; j++) {
            if(hasTeam[j] || visit[j]) continue;

            int next = edges[j];    // 다음 노드
            int order = 1;          // 순서
            visit[j] = order;       // 순서 저장

            vector<int> list;       // 방문 기록
            list.emplace_back(j);   // 첫 노드 저장

            while(1) {
                if(hasTeam[next]) break;    // 이미 팀이 있으면 break
                if(visit[next]) {           // 왔던 곳
                    if(list[visit[next] - 1] != next) break; // 이번에 방문한 곳이 아니라면

                    for(int k = visit[next] - 1; k < list.size(); k++) { // 방문 기록 순회
                        hasTeam[list[k]] = true;
                        ans--;
                    }
                }
                visit[next] = ++order;      // 순서 기록
                list.emplace_back(next);    // 방문 기록 저장
                next = edges[next];         // 다음 노드
            }
        }
        cout << ans << endl;
    }
}