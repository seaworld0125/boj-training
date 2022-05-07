#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

int virtual_s, virtual_e, virtual_k; // virtual start, end, k
vector<bool> arr; // 삭제 여부
stack<int> deleted; // 삭제된 요소

void U(int num) {
    while(num--) {
        virtual_k--;

        while(arr[virtual_k]) {
            virtual_k--;
        }
    }
}

void D(int num) {
    while(num--) {
        virtual_k++;

        while(arr[virtual_k]) {
            virtual_k++;
        }
    }
}

void C() {
    if(virtual_k == virtual_e) { // 마지막 행을 지우는 거라면
        deleted.emplace(virtual_e);
        arr[virtual_e] = true;
        virtual_e--;

        while(arr[virtual_e]) {
            virtual_e--;
        }
        virtual_k = virtual_e; // 마지막 요소를 가리키게끔
    }
    else if(virtual_k == virtual_s) { // 첫번째 행을 지우는 거라면
        deleted.emplace(virtual_s);
        arr[virtual_s] = true;
        virtual_s++;

        while(arr[virtual_s]) {
            virtual_s++;
        }
        virtual_k = virtual_s; // 마지막 요소를 가리키게끔
    }
    else { // 중간 요소를 지우는 거라면
        deleted.emplace(virtual_k);
        arr[virtual_k] = true;
        D(1); // 아래로 한 칸 이동
    }
}

void Z() {
    int restoreIdx = deleted.top();
    deleted.pop();

    if(virtual_s > restoreIdx) virtual_s = restoreIdx;
    else if(virtual_e < restoreIdx) virtual_e = restoreIdx;

    arr[restoreIdx] = false;
}

string solution(int n, int k, vector<string> cmd) {
    virtual_s = 0;
    virtual_e = n - 1;
    virtual_k = k;

    vector<bool>(n, false).swap(arr);

    int cmdSize = cmd.size();

    for(int i = 0; i < cmdSize; i++) {
        switch (cmd[i][0])
        {
        case 'U':
            U(stoi(cmd[i].substr(2)));
            break;
        case 'D':
            D(stoi(cmd[i].substr(2)));
            break;
        case 'C':
            C();
            break;
        case 'Z':
            Z();
            break;
        }
    }
    string answer(n, 'X');
    for(int i = 0; i < n; i++) {
        if(!arr[i]) answer[i] = 'O';
    }
    return answer;
}

void printStatus() {
    cout << "s : " << virtual_s << ", e : " << virtual_e << ", k : " << virtual_k << endl; 
    for(int i = 0; i < arr.size(); i++) {
        cout << arr[i] << ' ';
    }cout << endl;
}

int main() {
    string t = "123456";
    cout << t.substr(2);
}