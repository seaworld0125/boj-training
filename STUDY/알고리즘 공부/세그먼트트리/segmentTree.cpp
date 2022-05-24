#include <iostream>
#include <vector>
using namespace std;

struct SegmentTree {
    int size;
    vector<int> tree;

    int opt(int left, int right) {
        // sum
        return left + right;
    }

    int buildRecursive(const int arr[], int node, int left, int right) {
        if(left == right) {
            return tree[node] = arr[left];
        }

        int mid = (left + right) / 2;
        int lVal = buildRecursive(arr, node * 2, left, mid);
        int rVal = buildRecursive(arr, node * 2 + 1, mid + 1, right);

        return tree[node] = opt(lVal, rVal);
    }

    SegmentTree(const int arr[], int size) {
        this->size = size;
        this->tree.resize(size * 4);
        
        buildRecursive(arr, 1, 0, size - 1);
    }

    /*
        qLeft = query left index
        qRight = query Right index
        node = 현재 segmentTree node
        left = 현재 segmentTree node의 cover left index
        right = 현재 segmentTree node의 cover right index
    */
    int rangeQuery(int qLeft, int qRight, int node, int left, int right) {
        // 범위를 벗어난다면 Query 연산에 영향이 없는 값(0)을 return한다.
        if(right < qLeft || qRight < left) {
            return 0;
        }

        // 범위에 들어온다면 segmentTree에 저장되어 있는 값을 return
        if(qLeft <= left && right <= qRight) {
            return this->tree[node];
        }

        int mid = (left + right) / 2;
        int lVal = rangeQuery(qLeft, qRight, node * 2, left, mid);
        int rVal = rangeQuery(qLeft, qRight, node * 2 + 1, mid + 1, right);
    
        return opt(lVal, rVal);  
    }

    /*
        updateVal = update value
        index = update index
        node = 현재 segmentTree node
        left = 현재 segmentTree node의 cover left index
        right = 현재 segmentTree node의 cover right index
    */
    int updateQeury(int updateVal, int index, int node, int left, int right) {
        // update index가 현재 범위 밖이라면
        if(index < left || right < index) {
            return this->tree[node];
        }

        // update index에 도달했다면
        if(left == right) {
            return this->tree[node] = updateVal;
        }

        int mid = (left + right) / 2;
        int lVal = updateQeury(updateVal, index, node * 2, left, mid);
        int rVal = updateQeury(updateVal, index, node * 2 + 1, mid + 1, right);

        return tree[node] = opt(lVal, rVal);
    }
};

int main() {
    int arr[] = {13, 29, 1, 11, 77};
    int size = 5;

    SegmentTree segTree(arr, size);

    cout << "(2 ~ 3) range sum = " << segTree.rangeQuery(2, 3, 1, 0, size - 1) << endl;
    
    cout << "update arr[3] => 22\n"; segTree.updateQeury(22, 3, 1, 0, size - 1);

    cout << "(2 ~ 3) range sum = " << segTree.rangeQuery(2, 3, 1, 0, size - 1) << endl;
}

/*
output
>> (2 ~ 3) range sum = 12
>> update arr[3] => 22
>> (2 ~ 3) range sum = 23
*/