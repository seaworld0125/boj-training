#include <iostream>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

int N, K, ans = 0;
int sArr[51]; // 앞뒤 자르고 필요한 단어 bit 형태로 저장

void DFS(int state) {
    if(bitset<27>(state).count() > K) return;

    int count = 0;
    for(int i = 0; i < N; i++) {
        if((sArr[i] & state) == sArr[i]) { // 새롭게 확인한 문자열 // (이런 방법이...)
            count++;
        }
    }
    ans = max(ans, count);
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> N >> K;

    string tmp;
    for(int i = 0; i < N; i++) {
        cin >> tmp;

        sArr[i] = 0;
        for(int j = 0; j < tmp.length(); j++) {
            sArr[i] |= (1 << tmp[j] - 'a');
        }
    }
    if(K < 5) {
        cout << 0;
    }
    else if(K == 26) {
        cout << N;
    }
    else {
        int basicState = 0;
        basicState |= (1 << ('a' - 'a'));
        basicState |= (1 << ('c' - 'a'));
        basicState |= (1 << ('i' - 'a'));
        basicState |= (1 << ('n' - 'a'));
        basicState |= (1 << ('t' - 'a'));

        for(int i = 0; i < (1 << 26); i++) {
            if((basicState & i) != basicState) continue; // 연산자 우선순위에 주의할것....
            DFS(i);
        }
        cout << ans;
    }
}