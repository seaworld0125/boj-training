#include <iostream>
#include <vector>
using namespace std;

int N, M;

void recursive(int idx, vector<int> & list) {
    if(list.size() == M) {
        for(int i : list)
            cout << i << ' ';
        cout << endl;
        return;
    }

    for(int i = idx + 1; i <= N; i++) {
        list.emplace_back(i);
        recursive(i, list);
        list.pop_back();
    }
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;

    vector<int> list;
    for(int i = 1; i <= N; i++) {
        if(N - i < M - 1) break;

        list.emplace_back(i);
        recursive(i, list);
        list.pop_back();
    }
}