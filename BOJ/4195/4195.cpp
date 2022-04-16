#include <cstdio>
#include <cstring>
#include <string>
#include <map>
using namespace std;

#define MAX 200002

int T, F, count;
int parent[MAX];
int childs[MAX];
map<string, int> nameMap;

int findParent(int now) {
    if(parent[now] == now) return now;
    return parent[now] = findParent(parent[now]);
}

int unionParent(int a, int b) {
    a = findParent(a); 
    b = findParent(b);

    if(a == b) return childs[a];
    if(a < b) {
        parent[b] = a;

        childs[a] += childs[b];
        childs[b] = 0;

        return childs[a];
    }
    else {
        parent[a] = b;

        childs[b] += childs[a];
        childs[a] = 0;

        return childs[b];
    }
}

int main() {
    scanf("%d", &T);

    for(int i = 0; i < T; i++) {
        scanf("%d", &F);
        
        count = 0;
        nameMap.clear();

        for(int i = 1; i < MAX; i++) {
            parent[i] = i;
            childs[i] = 1;
        }

        for(int j = 0; j < F; j++) {
            char a[21];
            char b[21];
            int aIdx, bIdx;

            scanf("%s", a);
            scanf("%s", b);

            string sa(a);
            string sb(b);

            if(nameMap.find(sa) == nameMap.end()) { // 없는 이름이라면
                nameMap.emplace(sa, ++count);
            }
            aIdx = nameMap[sa];
            if(nameMap.find(sb) == nameMap.end()) {
                nameMap.emplace(sb, ++count);
            }
            bIdx = nameMap[sb];

            printf("%d\n", unionParent(aIdx, bIdx));
        }
    }
}