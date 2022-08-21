#include <queue>
#include <string>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;

#define ll long long

int solution(vector<int> queue1, vector<int> queue2) {
    int totalSize = (queue1.size() + queue2.size()) * 2;

    ll sum1 = accumulate(queue1.begin(), queue1.end(), 0LL);
    ll sum2 = accumulate(queue2.begin(), queue2.end(), 0LL);

    if((sum1 + sum2) % 2) {
        return -1;
    }

    deque<int> dequeue1(queue1.begin(), queue1.end()); 
    deque<int> dequeue2(queue2.begin(), queue2.end()); 

    int answer = 0;
    while(sum1 != sum2) {
        if(sum1 > sum2) {
            auto num = dequeue1.front();
            dequeue2.push_back(num);
            dequeue1.pop_front();
            sum2 += num;
            sum1 -= num;
        }
        else if(sum1 < sum2) {
            auto num = dequeue2.front();
            dequeue1.push_back(num);
            dequeue2.pop_front();
            sum1 += num;
            sum2 -= num;
        }
        answer++;
        if(totalSize < answer) return -1;
    }
    return answer;
}

int main() {
    solution({3, 2, 7, 2}, {4, 6, 5, 1});
}