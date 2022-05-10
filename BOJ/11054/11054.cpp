#include <iostream>
#include <string>
#include <stack>
using namespace std;

void check(string problem) {

    int size = problem.size();
    stack<char> st;

    for(char c : problem) {
        if(c == '(') {
            st.emplace(c);
        }
        else {
            if(st.empty()) {
                cout << "NO\n";
                return;
            }
            else {
                st.pop();
            }
        }
    }
    if(st.empty())
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    int T;
    cin >> T;

    string problem;
    while(T--) {
        cin >> problem;
        check(problem);
    }
}