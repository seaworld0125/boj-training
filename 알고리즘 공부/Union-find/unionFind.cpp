#include <iostream>
using namespace std;

int findParent(int* parent, int now) {
    if(parent[now] == now) return now;
    return now = findParent(parent, parent[now]);
}

void unionParent(int* parent, int a, int b) {
    a = findParent(parent, a);
    b = findParent(parent, b);
    if(a < b) parent[b] = a;
    else parent[a] = b;
}

bool checkParent(int* parent, int a, int b) {
    a = findParent(parent, a);
    b = findParent(parent, b);
    return a == b;
}

void printParent(int* parent) {
    cout << "node\t";
    for(int i = 1; i < 11; i++) cout << i << ' ';
    cout << endl << "parent\t";
    for(int i = 1; i < 11; i++) cout << parent[i] << ' ';
    cout << "\n_________________________________________________\n";
}

int main() {
    int parent[11];
    for(int i = 1; i < 11; i++) parent[i] = i;

    // 처음 부모 노드 출력
    printParent(parent);
    
    /*
    출력 결과
    node    1 2 3 4 5 6 7 8 9 10
    parent  1 2 3 4 5 6 7 8 9 10
    */

    // 1과 2를 연결
    unionParent(parent, 1, 2);
    printParent(parent);
    
    /*
    출력 결과
    node    1 2 3 4 5 6 7 8 9 10
    parent  1 1 3 4 5 6 7 8 9 10
    */

    // 3과 4, 4와 5, 5와 6을 연결
    unionParent(parent, 3, 4);
    unionParent(parent, 4, 5);
    unionParent(parent, 5, 6);
    printParent(parent);
    
    /*
    출력 결과
    node    1 2 3 4 5 6 7 8 9 10
    parent  1 1 3 3 3 3 7 8 9 10
    */

    // 2와 6을 연결
    unionParent(parent, 2, 6);
    printParent(parent);
    
    /*
    출력 결과
    node    1 2 3 4 5 6 7 8 9 10
    parent  1 1 1 3 3 3 7 8 9 10
    */
}