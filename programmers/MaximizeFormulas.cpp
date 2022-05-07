#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <deque>
#include <cmath>
using namespace std;

string Exp;
char opts[] = {'*', '+', '-'};
map<char, int> optMap;
long long answer = 0;

deque<long long> numDeque;
deque<char> optDeque;

void calc() {
    long long b = numDeque.back();
    numDeque.pop_back();
    long long a = numDeque.back();
    numDeque.pop_back();
    char opt = optDeque.back();
    optDeque.pop_back();

    if(opt == '*') {
        // cout << a << " *= " << b << endl;
        a *= b;
    }
    else if(opt == '-') {
        // cout << a << " -= " << b << endl;
        a -= b;
    }
    else {
        // cout << a << " += " << b << endl;
        a += b; 
    }
    numDeque.push_back(a);
}

void operation() {
    numDeque.clear();
    optDeque.clear();

    vector<int> numList;
    vector<char> optList;

    string num = "";
    for(int i = 0; i < Exp.size(); i++) { // 문자열 자르기
        if(Exp[i] >= '0' && Exp[i] <= '9') {
            num += Exp[i];
        }
        else {
            numList.push_back((long long)stoi(num));
            optList.push_back(Exp[i]);
            num = "";
        }
        if(i + 1 == Exp.size()) {
            numList.push_back((long long)stoi(num));
            break;
        }
    }

    numDeque.push_back(numList[0]);

    for(int i = 0; i < optList.size(); i++) {
        char opt = optList[i];

        while(!optDeque.empty() && optMap[optDeque.back()] <= optMap[opt]) {
            calc();
        }
        numDeque.push_back(numList[i + 1]);
        optDeque.push_back(opt);
    }

    while(numDeque.size() > 1) {
        calc();
    }

    long long result = numDeque.back();
    result *= (result < 0 ? -1 : 1); 
    // cout << "result >> " << result << endl;
    answer = max(answer, result);
}

void setPriority(int count) {
    if(count > optMap.size()) {
        // 우선순위가 모두 설정 완료되었다면 연산을 시작한다
        operation();
    }

    for(int i = 0; i < 3; i++) {
        auto key = optMap.find(opts[i]);
        
        // key를 가지고 있고 아직 우선순위가 설정되지 않았다면  
        if(key != optMap.end() && key->second == 0) {   
            key->second = count;

            // 다음 우선순위 설정
            setPriority(count + 1); 
            key->second = 0;
        }
    }
}

long long solution(string expression) {    
    Exp = expression;
    for(int i = 0; i < expression.size(); i++) {
        char c = expression[i];
        if(c == '-' || c == '+' || c == '*') {
            optMap[c] = 0;
        }
    }

    setPriority(1);
    return answer;
}

int main() {
    cout << "ans : " << solution("100*200-50");
}