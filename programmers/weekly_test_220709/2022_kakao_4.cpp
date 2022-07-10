#include <iostream>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
using namespace std;

#define pii pair<int, int>
#define F first
#define S second
#define endl '\n'
#define INF (int)1e9

/*
    완탐
*/

const int MAX_ARR_SIZE = 11;

bool isBetterAns(vector<int>& now, vector<int>& answer) {
    for(int i = MAX_ARR_SIZE - 1; i >= 0; i--)
        if(now[i] > answer[i]) 
            return true;
        else if(now[i] < answer[i])
            return false;
}

// return <now, info>
pii getScore(vector<int>& now, vector<int>& info) {
    pii score = {0, 0};
    for(int i = 0; i < MAX_ARR_SIZE; i++) {
        if(info[i] < now[i])
            score.F += (10 - i);
        else if(info[i])
            score.S += (10 - i);
    }
    return score;
}

void renewAnswer(pii& score, vector<int>& now, vector<int>& answer, int& maxScoreDiff) {
    int nowScoreDiff = score.F - score.S;

    if(maxScoreDiff <= nowScoreDiff) {
        if(maxScoreDiff == nowScoreDiff && !isBetterAns(now, answer)) return;

        maxScoreDiff = nowScoreDiff;
        answer.assign(now.begin(), now.end()); 
    }
}

void solve(int n, int pos, vector<int>& now, vector<int>& info, vector<int>& answer, int& maxScoreDiff) {
    if(n == 0 || pos == 11) {
        now[MAX_ARR_SIZE - 1] += n;
        pii score = getScore(now, info);
        renewAnswer(score, now, answer, maxScoreDiff);
        now[MAX_ARR_SIZE - 1] -= n;

        return;
    }

    // 얻을 수 있는 점수라면 얻는다
    if(info[pos] < n) {
        int reqShot = info[pos] + 1;
        now[pos] += reqShot;
        solve(n - reqShot, pos + 1, now, info, answer, maxScoreDiff);
        now[pos] -= reqShot;
    }

    // 얻지 않는 경우
    solve(n, pos + 1, now, info, answer, maxScoreDiff);
}

vector<int> solution(int n, vector<int> info) {
    vector<int> answer(1, -1);
    int maxScoreDiff = 0;

    vector<int> now(11, 0);

    solve(n, 0, now, info, answer, maxScoreDiff);

    return answer;
}

int main() {
    vector<vector<int>> arr = {
        {2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 2, 0, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 3},
        {0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    
    vector<int> nArr = {
        5,
        1, 
        9, 
        10,
        10
    };

    for(int i = 0; i < arr.size(); i++) {
        auto answer = solution(nArr[i], arr[i]);
        cout << "==================answer==================\n";
        for(int n : answer) {
            cout << n << " ";
        }
        cout << endl;
    }
}