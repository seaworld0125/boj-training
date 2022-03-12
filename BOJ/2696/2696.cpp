#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);

    for(int i = 0; i < T; i++) {
        int M, swap = 0;
        scanf("%d", &M);

        priority_queue<int> pq[2];
        vector<int> ans;

        for(int j = 0; j < M; j++) {
            int num;
            scanf("%d", &num);

            pq[swap].emplace(num);

            if(j % 2 == 0) {
                int mid = j / 2;

                for(int k = 0; k < j + 1; k++) {
                    if(k == mid) {
                        ans.emplace_back(pq[swap].top());
                    }
                    pq[(swap + 1) % 2].emplace(pq[swap].top());
                    pq[swap].pop();
                }
                swap = (swap + 1) % 2;
            }
        }
        int size = ans.size();

        printf("%d\n", size);
        for(int j = 1; j <= size; j++) {
            printf("%d ", ans[j - 1]);
            if(j % 10 == 0) printf("\n");
        }
    }
}