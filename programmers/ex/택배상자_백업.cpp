#include <string>
#include <vector>
#include <stack>

using namespace std;

int solution(vector<int> order) {
    int answer = 0;
    int size = order.size();

    stack<int> s;
    

    for(int i = 1, j = 0; j < size;) {
        if(order[j] == i) {
            answer++, i++, j++;
        }
        else {
            if(!s.empty() && (s.top() == order[j])) {
                s.pop();
                answer++, j++;
            }
            else {
                s.push(i);
                i++;

                if(i > size) break;
            }
        }
    }

    return answer;
}