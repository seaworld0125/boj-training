#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int parent[101];
int score[101] = {0};

int findParent(int a) {
    if(parent[a] == a) return a;
    return parent[a] = findParent(parent[a]);
}

bool unionParent(int a, int b) {
    a = findParent(a);
    b = findParent(b);

    if(a == b) return false;
    if(a > b) parent[a] = b;
    else parent[b] = a;
    return true;
}

void visit(int &n, vector<int> &cards) {
    if(unionParent(n, cards[n - 1])) {
        visit(cards[n - 1], cards);
    }
}

int solution(vector<int> cards) {
    int size = cards.size() + 1;

    for(int i = 1; i < size; i++) {
        parent[i] = i;
    }

    for(int &n : cards) {
        visit(n, cards);
    }

    for(int i = 1; i < size; i++) {
        score[parent[i]]++;
    }
    sort(score, score + 101, greater<int>());


    return score[0] * score[1];
}