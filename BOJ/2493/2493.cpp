#include <iostream>
#include <stack>
using namespace std;

struct NumInfo {
    int num;
    int idx;

    NumInfo(int n, int i):num(n), idx(i) {}
};

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, num;
    stack<NumInfo> stk;

    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> num;

        while(!stk.empty()) {
            if(stk.top().num > num) {
                cout << stk.top().idx << ' ';
                break;
            }
            stk.pop();
        }
        if(stk.empty()) cout << "0 ";
        
        stk.emplace(num, i);
    }
}