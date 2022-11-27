#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

/*
    확실히 일반 set 보다 unordered_set으로 했을 때 더 빨랐다. 
    
    unordered_set은 평균 100ms 내외로 나온다.
    set은 평균 200ms는 넘는 것 같다.

    아무래도 unordered_set이 해쉬테이블로 구현되어 있기 때문에 그렇다.

    이 문제는 순회할 일이 없기 때문에 unordered_set으로 중복처리 해도 좋을 것 같다.
*/

int solution(vector<int> elements) {

    int size = elements.size();
    unordered_set<int> res;

    for(int i = 0; i < size; i++) {

        int sum = 0;

        for(int j = i; j < i + size; j++) {
            sum += elements[j % size];
            res.emplace(sum);
        }
    }
    return res.size();
}