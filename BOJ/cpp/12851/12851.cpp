#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int N, K;
bool visited[100001];

int min_time;
int cnt = 0;

void bfs() {

    queue<int> visit;
    visit.push(N);
    visited[N] = true;

    int time = 0;
    bool end = false;

    while(!visit.empty()) { 

        int size = visit.size();
        vector<int> next;

        for(int i = 0; i < size; i++) {

            auto now = visit.front();
            visit.pop();

            if(now == K) {
                min_time = time;
                cnt++;
                end = true;
            }

            if(now < 100001 && !visited[now + 1]) {
                visit.push(now + 1);
                next.push_back(now + 1);
            }
            if(now > 0 && !visited[now - 1]) {
                visit.push(now - 1);
                next.push_back(now - 1);
            }
            if(now * 2 < 100001 && !visited[now * 2]) {
                visit.push(now * 2);
                next.push_back(now * 2);
            }
        }

        if(end) return;
        for(auto i : next) visited[i] = true;
        time++;
    }
}

int main() {

    cin >> N >> K;

    if(N == K) {
        printf("0\n1");
        return 0;
    }

    memset(visited, 0, sizeof(visited));

    bfs();

    printf("%d\n%d", min_time, cnt);
}