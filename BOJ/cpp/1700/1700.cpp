#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, K, ans = 0;
    cin >> N >> K;

    bool used[101];
    fill_n(used, 101, false);
    vector<int> multitap;
    vector<int> order(K);

    for(int i = 0; i < K; i++) cin >> order[i];

    for(int i = 0; i < K; i++) {
        // 이미 꽂혀 있으면 건너뜀
        if(used[order[i]]) continue;

        // 빈 자리 있으면 꽂기
        if(multitap.size() < N) {
            multitap.emplace_back(order[i]);
            used[order[i]] = true;
        }
        else {
            // 가장 오래 안쓰이는 전자제품 뽑기
            int needPoint = -1; // 가장 늦는 시점
            int index = -1;     // 해당 제품 index

            for(int j = 0; j < multitap.size(); j++) {
                int tmp = 0; // 제품이 쓰이는 시점

                for(int m = i; m < K; m++) {
                    if(multitap[j] == order[m]) {
                        break;
                    }   
                    tmp++;
                }
                if(tmp > needPoint) { // 최신화
                    index = j;
                    needPoint = tmp;
                }
            }
            used[multitap[index]] = false; // 사용 여부 갱신
            multitap[index] = order[i];
            used[order[i]] = true; 
            ans++;
        }
    }
    cout << ans;
}