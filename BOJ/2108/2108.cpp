#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

#define endl '\n'

// 산술 평균
double sum = 0;

// 중앙값
int numArr[500001];

// 최빈값 - 계수 정렬 사용
int positiveArr[4001] = {0};
int negativeArr[4001] = {0};

// 범위
int maxNum = -(int)1e9;
int minNum = (int)1e9;

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N;
    cin >> N;

    for(int i = 0; i < N; i++) {
        cin >> numArr[i];

        sum += numArr[i];

        if(numArr[i] < 0)
            negativeArr[abs(numArr[i])]++;
        else
            positiveArr[numArr[i]]++;

        maxNum = max(maxNum, numArr[i]);
        minNum = min(minNum, numArr[i]);
    }

    vector<pair<int, int>> coefficientArr;

    for(int i = 0; i < 4001; i++) {
        if(positiveArr[i] != 0)
            coefficientArr.emplace_back(positiveArr[i], i);

        if(negativeArr[i] != 0)
            coefficientArr.emplace_back(negativeArr[i], -i);
    }

    sort(coefficientArr.begin(), coefficientArr.end(), [](pair<int, int> & a, pair<int, int> & b) {
        if(a.first > b.first) return true;
        else if(a.first == b.first) {
            return a.second < b.second;
        }
        else return false;
    }); 

    sort(numArr, numArr + N);

    cout << (int)round((floor((sum / N) * 10)) / 10) << endl;
    cout << numArr[N / 2] << endl;
    cout << (coefficientArr[0].first == coefficientArr[1].first ? coefficientArr[1].second : coefficientArr[0].second) << endl;
    cout << maxNum - minNum;
}