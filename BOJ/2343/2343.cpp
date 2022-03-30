#include <iostream>
#include <algorithm>
using namespace std;

#define ll long long

ll N, M;
ll lecture[100001];

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;

    ll left = 0, right = 100000 * 10000;

    for(int i = 0; i < N; i++) {
        cin >> lecture[i];
        left = max(left, lecture[i]);
    }

    ll mid, sum, m, ans;

    while(left <= right) {              
        mid = (left + right) / 2;       // 비디오 최대 길이
        
        sum = 0;                        // 비디오 길이
        m = 1;                          // 비디오 개수
        for(int i = 0; i < N; i++) {
            sum += lecture[i];
            
            if(sum > mid) {             // 현재 비디오 길이가 최대 길이보다 길다면
                sum = lecture[i];       // 더한거 취소
                m++;                    // 비디오 개수 증가
                if(m > M) break;        // 비디오 개수가 더 많다면 break
            }
        }
        if(m > M)                       // 비디오 개수가 최대 개수보다 많다면 최대 비디오 길이를 늘려줘야 함
            left = mid + 1;
        else {                          // 널널하다면 비디오 최대 길이 줄여주고 답 갱신
            right = mid - 1;
            ans = mid;
        }
    }
    cout << ans;
}