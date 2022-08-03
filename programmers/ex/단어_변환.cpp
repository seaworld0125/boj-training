#include <queue>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

vector<int> edges[51];

inline int compWord(string& a, string& b) {
    int size = a.size(),
        count = 0;

    for(int i = 0; i < size; i++)
        if(a[i] != b[i]) 
            count++;

    return count;
}

int initialize(string& begin, string& target, vector<string>& words) {
    words.push_back(words[0]);
    words[0] = begin;

    int size = words.size();
    int targetIdx = 0;
    
    for(int i = 0; i < size; i++) {
        if(words[i] == target) {
            targetIdx = i;
        }
        for(int j = 0; j < size; j++) {
            if(i == j || words[i] == words[j]) continue;
            if(compWord(words[i], words[j]) > 1) continue;
            edges[i].emplace_back(j);
        }
    }
    return targetIdx;
}

int BFS(int targetIdx) {
    bool visited[52];
    memset(visited, 0, sizeof(visited));
    visited[0] = true;

    queue<int> visit;
    visit.emplace(0);

    int dist = 0;
    while(!visit.empty()) {
        for(int i = 0; i < visit.size(); i++) {
            int now = visit.front();
            visit.pop();

            if(now == targetIdx) {
                return dist;
            }

            int size = edges[now].size();
            for(int j = 0; j < size; j++) {
                int next = edges[now][j];
                if(visited[next]) continue;

                visit.emplace(next);
                visited[next] = true;
            }
        }
        dist++;
    }
    return dist;
}

int solution(string begin, string target, vector<string> words) {
    int targetIdx = initialize(begin, target, words);
    if(targetIdx) return BFS(targetIdx); 
    return 0;
}