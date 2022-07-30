#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <regex>
using namespace std;

#define ALPHABET 26
#define TRIE first
#define IDX second
/*
    https://school.programmers.co.kr/learn/courses/30/lessons/60060
    
    reverse trie를 사용해야 2,3번 효율성을 통과할 수 있었다.
    reverse trie와 count 개념을 함께 사용해야 1번 효율성을 통과할 수 있었다.

    앞으로 Trie를 쓸 때 insert나 find 매서드를 재귀 대신 단순 반복문으로 구현하자.
*/

struct Trie {
    Trie* arr[ALPHABET];
    int count;

    Trie() {
        memset(arr, 0, sizeof(arr));
        count = 0;
    }

    ~Trie() {
        for(int i = 0; i < ALPHABET; i++)
            if(arr[i])
                delete arr[i];
    }

    void insert(const string& key) {
        auto* now = this;
        for(const char& c : key) {
            now->count++;
            if(now->arr[c - 'a'] == NULL)
                now->arr[c - 'a'] = new Trie();
            now = now->arr[c - 'a'];
        }
    }

    int find(const string& key) {
        auto* now = this;
        for(const char& c : key) {
            if(c == '?') {
                return now->count;    
            }
            now = now->arr[c - 'a'];
            if(now == NULL) {
                return 0;
            }
        }
        return -1;
    }
};

Trie trie[10001];
Trie reverseTrie[10001];
int wordCount[10001];
regex r("\\W*");

vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer;

    memset(wordCount, 0, sizeof(wordCount));

    int size;
    for(string& word : words) {
        size = word.size();
        
        trie[size].insert(word);
        reverse(word.begin(), word.end());
        reverseTrie[size].insert(word);
        wordCount[size]++;
    }

    for(string& query : queries) {
        size = query.size();

        if(regex_match(query, r)) {
            answer.emplace_back(wordCount[size]);
        }
        else {
            if(query[0] == '?') {
                reverse(query.begin(), query.end());
                answer.emplace_back(reverseTrie[size].find(query));   
            }
            else {
                answer.emplace_back(trie[size].find(query));   
            }
        }
    }
    return answer;
}


int main() {
    vector<vector<string>> wordsList = {
        {"frodo", "front", "frost", "frozen", "frame", "kakao"},

    };

    vector<vector<string>> queriesList = {
        {"fro??", "????o", "fr???", "fro???", "pro?", "??????", "?????"},

    };

    vector<vector<int>> resultList = {
        {3, 2, 4, 1, 0},

    };

    for(int i = 0; i < wordsList.size(); i++) {

        vector<int> result = solution(wordsList[i], queriesList[i]);

        for(int n : result) {
            cout << n << ", ";
        }cout << endl;
    }
}