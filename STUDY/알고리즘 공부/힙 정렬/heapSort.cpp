#include <iostream>
using namespace std;

int main() {
    int MAX = 5;
            //    0, 1, 2, 3, 4
    int tree[] = {2, 4, 1, 7, 5};

    for(int i = 1; i < MAX; i++) { // 최초로 힙 구조를 형성
        int child = i;
        do {
            int parent = (child - 1) / 2;
            
            if(tree[parent] < tree[child]) { // 부모 노드가 더 작다면 교환
                int tmp = tree[parent];
                tree[parent] = tree[child];
                tree[child] = tmp; 
            }

            child = parent;
        } while(child != 0);
    }

    for(int i = 0; i < MAX; i++) cout << tree[i] << ' ';
    cout << endl;

    /*
    output
    7 5 1 2 4
    */

    for(int i = MAX - 1; i >= 0; i--) { // 크기를 1씩 줄여가며 힙 구성
        int tmp = tree[0]; // 가장 큰 값을 가장 아래로
        tree[0] = tree[i];
        tree[i] = tmp;

        int parent = 0;
        int child = 1;

        do {
            child = 2 * parent + 1;

            // 두개의 자식 노드 중에 더 큰 노드를 찾는다.
            if(child < i - 1 && tree[child] < tree[child + 1]) {
                child++;
            }

            // 더 큰 자식 노드가 부모 노드보다 크다면
            if(child < i && tree[parent] < tree[child]) {
                tmp = tree[parent];
                tree[parent] = tree[child];
                tree[child] = tmp;
            }

            parent = child;
        } while(child < i);
    }

    for(int i = 0; i < MAX; i++) cout << tree[i] << ' ';
    cout << endl;

    /*
    output
    1 2 4 5 7
    */
}