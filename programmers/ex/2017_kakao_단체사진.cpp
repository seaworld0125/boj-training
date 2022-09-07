#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

bool check(unordered_map<char, int>& umap, vector<char>& member, vector<string>& data) {
    char mem1, mem2, inequality;
    int dist, ndist;

    for(auto d : data) {

        mem1 = d[0];
        mem2 = d[2];
        inequality = d[3];
        dist = d[4] - '0';
        ndist = abs(abs(umap[mem1] - umap[mem2]) - 1);

        if(inequality == '=' && ndist != dist) return false;

        if(inequality == '>' && ndist <= dist) return false;

        if(inequality == '<' && ndist >= dist) return false;
    }
    return true;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, vector<string> data) {
    int answer = 0;
    unordered_map<char, int> umap;
    vector<char> member = {'A', 'C', 'F', 'J', 'M', 'N', 'R', 'T'};
    int memSize = member.size();

    do
    {
        for(int i = 0; i < memSize; i++) {
            umap[member[i]] = i;
        }
        if(check(umap, member, data)) {
            answer++;
        }
    } while (next_permutation(member.begin(), member.end()));
    
    return answer;
}