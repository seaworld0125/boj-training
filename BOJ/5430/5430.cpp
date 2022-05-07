#include <iostream>
#include <queue>
#include <string>
using namespace std;

void solve(deque<int>& dq, string& func) {
    bool flip = false;
    int size = func.size();

    for(int i = 0; i < size; i++) {
        if(func[i] == 'R') flip = !flip;
        else {
            if(dq.empty()) {
                cout << "error\n";
                return;
            }
            if(flip) dq.pop_back();
            else dq.pop_front();
        }
    }
    cout << '[';
    while(!dq.empty()) {
        if(flip) {
            cout << dq.back();
            dq.pop_back();
        }
        else {
            cout << dq.front();
            dq.pop_front();
        }
        if(!dq.empty()) cout << ',';
    }
    cout << "]\n";
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    int T;
    cin >> T;

    string func, arr;
    int n;

    while(T--) {
        cin >> func  >> n >> arr;

        deque<int> dq;

        if(n) {
            for(int i = 1, idx = 1; i < arr.size(); i++) {
                if(arr[i] == ',' || arr[i] == ']') {
                    dq.emplace_back(stoi(arr.substr(idx, i - idx)));
                    i++;
                    idx = i;
                }
            }
        }
        solve(dq, func);
    }
}