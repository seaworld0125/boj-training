#include <iostream>
#include <algorithm>
using namespace std;

int N, C, house[200000];

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> N >> C;

    for(int i = 0; i < N; i++)
        cin >> house[i];

    sort(house, house + N);

    int left = 0, 
        right = (int)1e9, 
        mid, 
        dist, 
        c, 
        ans;

    while(left <= right) {
        mid = (left + right) / 2;   // 기준 거리
        c = C - 1;                  // 공유기 수
        dist = house[0];            // 공유기의 거리

        for(int i = 1; i < N; i++) { // 배열을 순회하면서 기준에 맞으면 공유기를 설치해본다
            if(house[i] - dist >= mid) { // 조건 : 기준 거리보다 거리가 멀거나 같으면 설치한다
                dist = house[i];
                c--;
                if(c == 0) break;
            }
        }
        if(c > 0) { // 공유기를 설치하지 못했으면 기준 거리가 너무 먼 것이므로
            right = mid - 1;
        } 
        else { // 공유기를 다 설치했으면 기준 거리가 충분히 좁은 것이므로
            left = mid + 1;
            ans = mid;
        }
    }
    cout << ans;
}