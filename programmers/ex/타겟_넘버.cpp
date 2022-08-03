#include <vector>
#include <iostream>
using namespace std;

int answer = 0;

void recursive(vector<int>& numbers, int sum, int idx) {
    if(idx == numbers.size()) {
        if(sum == 0) answer++;
        return;
    }
    recursive(numbers, sum + numbers[idx], idx + 1);
    recursive(numbers, sum - numbers[idx], idx + 1);
}

int solution(vector<int> numbers, int target) {
    recursive(numbers, target, 0);
    return answer;
}