#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Trie {
    bool finish;
    Trie* node[10];

    Trie() {
        finish = false;
        fill(node, node + 10, nullptr);
    }

    ~Trie() {
        for(int i = 0; i < 10; i++) 
            if(node[i] != NULL)
                delete node[i];
    }

    void insert(char* str) {
        if(*str == '\0') {finish = true; return;}
        
        int cur = *str - '0';
        if(node[cur] == NULL) node[cur] = new Trie();

        node[cur]->insert(str + 1);
    }

    bool find(char * str) {
        if(*str == '\0') return false;
        if(finish) return true;

        int cur = *str - '0';
        return node[cur]->find(str + 1);
    }
};

int main() {ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int t, n;

    cin >> t;
    for(int i = 0; i < t; i++) {
        cin >> n;
        Trie* root = new Trie();
        char cstr[10000][11];
        bool flag = false;

        for(int i = 0; i < n; i++) {
            cin >> cstr[i];
            root->insert(cstr[i]);
        }
        for(int i = 0; i < n && !flag; i++) {
            flag = root->find(cstr[i]);
        }

        cout << (flag ? "NO\n" : "YES\n");
        delete root;
    }
}