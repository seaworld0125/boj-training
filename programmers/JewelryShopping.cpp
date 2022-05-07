#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

#include <iostream>

using namespace std;

vector<int> solution(vector<string> gems) {
    set<string> targetGemList; // 포함해야 하는 보석 리스트
    map<string, int> gemCount; // 현재 내가 가진 보석 개수 map

    for(string gem : gems) {
        if(gemCount.find(gem) == gemCount.end()) {
            gemCount[gem] = 0;
            targetGemList.emplace(gem);
        }
    }

    vector<int> answer(2); // 정답
    int len = (int)1e9; // 정답 길이
    
    set<string> myGemList; // 내가 가진 보석 리스트

    int left = 0, right = 0;
    gemCount[gems[left]]++; // 첫번째 보석 포함시키기
    myGemList.emplace(gems[left]);

    while(1) { 
        if(myGemList.size() == targetGemList.size()) { // 모든 보석을 포함했다면 
            
            while(left != right && gemCount[gems[left]] > 1) { // left < right && 보석 개수 > 1

                gemCount[gems[left]]--; // 보석 빼기
                left++; // 모든 보석을 포함하는 최소 구간까지 left를 증가시키기
            }
            if(len > right - left) { // 답 갱신
                answer[0] = left + 1;
                answer[1] = right + 1;
                len = right - left;    
            }
        }    
        if(right + 1 == gems.size()) break; // 더 이상 right를 늘릴 수 없다면 종료

        right++; // 모든 보석을 포함할 때 까지 right를 증가시키기
        gemCount[gems[right]]++;
        myGemList.emplace(gems[right]);
    }
    return answer;
}

int main() {
    // vector<int> answer = solution({"DIA", "RUBY", "RUBY", "DIA", "DIA", "EMERALD", "SAPPHIRE", "DIA"});
    vector<int> answer = solution({"ZZZ", "YYY", "NNNN", "YYY", "BBB"});
    cout << answer[0] << ", " << answer[1];
}