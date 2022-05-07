#include <string>
#include <vector>
#include <stack>
using namespace std;

struct Node {
    int prev = -1;
    int next = -1;
    int val = -1;
};

string solution(int n, int k, vector<string> cmd) {
    string answer(n, 'O');
    vector<Node> list(n);
    stack<Node> deleted;

    for(int i = 0; i < n; i++) {
        list[i].val = i;
        if(i > 0) {
            list[i].prev = i - 1;
        }
        if(i < n - 1) {
            list[i].next = i + 1;
        }
    }

    int cmdSize = cmd.size();
    int count;
    int prev, next;

    for(int i = 0; i < cmdSize; i++) {
        switch (cmd[i][0])
        {
        case 'U':
            count = stoi(cmd[i].substr(2)); 
            while(count--) {
                k = list[k].prev;
            }
            break;
        case 'D':
            count = stoi(cmd[i].substr(2)); 
            while(count--) {
                k = list[k].next;
            }
            break;
        case 'C':
            prev = list[k].prev;
            next = list[k].next;    
            deleted.push(list[k]);

            if(prev > -1) { // 왼쪽에 노드가 있을 때
                list[prev].next = next;
            }
            if(next > -1) { // 오른쪽에 노드가 있을 때
                list[next].prev = prev;
            }
            k = next > -1 ? next : prev;

            break;
        case 'Z':
            Node node = deleted.top();
            deleted.pop();

            if(node.next != -1) { // 오른쪽에 노드가 있을 때
                list[node.next].prev = node.val;
            }
            if(node.prev != -1) { // 왼쪽에 노드가 있을 때
                list[node.prev].next = node.val;
            }
            break;
        }
    }
    while(!deleted.empty()) {
        answer[deleted.top().val] = 'X';
        deleted.pop();
    }
    return answer;
}