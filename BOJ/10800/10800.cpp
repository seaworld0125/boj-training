#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

struct Ball {
    int idx;
    int color;
    int size;
    int ret;
};

int sizePrefixSumArr[2001] = {0};
int colorPrefixSumArr[200001] = {0};

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);

    int N;
    cin >> N;

    vector<Ball> basicPrefixSum(N);

    int color, size;
    for(int i = 0; i < N; i++) { // N
        scanf("%d %d", &color, &size);
        auto& cur = basicPrefixSum[i];
        cur.idx = i;
        cur.color = color - 1;
        cur.size = size;
    }

    sort(basicPrefixSum.begin(), basicPrefixSum.end(), [](Ball& a, Ball& b) { // NlogN
        if(a.size == b.size)
            return a.color < b.color;
        else
            return a.size < b.size;
    });

    int prefix = 0;
    for(int i = 0; i < N; i++) { // N
        auto& ball = basicPrefixSum[i];

        prefix += ball.size;
        sizePrefixSumArr[ball.size] += ball.size;
        colorPrefixSumArr[ball.color] += ball.size;
    
        if(i > 0 && basicPrefixSum[i - 1].color == ball.color && basicPrefixSum[i - 1].size == ball.size) 
            ball.ret = basicPrefixSum[i - 1].ret;
        else
            ball.ret = prefix - colorPrefixSumArr[ball.color] - sizePrefixSumArr[ball.size] + ball.size;
    }

    sort(basicPrefixSum.begin(), basicPrefixSum.end(), [](Ball& a, Ball& b) { // NlogN
        return a.idx < b.idx;
    });

    for(auto& ball : basicPrefixSum) {
        printf("%d\n", ball.ret);
    }
}

// https://www.acmicpc.net/problem/10800