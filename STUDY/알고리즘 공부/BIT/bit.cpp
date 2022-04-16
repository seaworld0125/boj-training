#include <iostream>
#include <vector>
using namespace std;

#define MAX 1000001

int arr[MAX]; // original arr

struct BinaryIndexedTree {
    vector<int> bit;

    BinaryIndexedTree(int size) {
        bit.resize(size + 1, 0);

        for(int i = 0; i < size; i++) {
            this->updateBIT(i, arr[i]);
        }
    }

    void updateBIT(int originalIdx, int updateNum) {
        int idx = originalIdx + 1;

        int size = bit.size();

        while(idx <= size) {
            bit[idx] += updateNum;
            idx += (idx & -idx);
        }

        arr[originalIdx] = updateNum; // 업데이트되는 값으로 original arr 갱신
    }

    int getSum(int idx) {
        idx++;

        int sum = 0;

        while(idx > 0) {
            sum += bit[idx];
            idx -= (idx & -idx);
        }

        return sum;
    }
};

int main() {
    for(int i = 0; i < 12; i++) {
        arr[i] = i + 1; // 1부터 11까지 저장
    }

    BinaryIndexedTree BIT(12);

    cout << BIT.getSum(3) << endl; // 3번 인덱스까지의 합 = 1,2,3,4 의 합
    
    BIT.updateBIT(2, 10 - arr[2]);  // 2번 인덱스를 10으로 업데이트...
    arr[2] = 10;

    cout << BIT.getSum(3) << endl; // 3번 인덱스까지의 합 = 1,2,10,4 의 합

    BIT.updateBIT(3, -10 - arr[3]);  // 3번 인덱스를 -10으로 업데이트...
    arr[3] = -10;

    cout << BIT.getSum(3) << endl; // 3번 인덱스까지의 합 = 1,2,10,-10 의 합
}