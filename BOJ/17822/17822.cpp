#include <iostream>
#include <deque>
#include <vector>
#include <cstring>
using namespace std;

// 원판의 개수
int N; 
// 원판에 적힌 수의 개수
int M; 
// 총 회전 횟수
int T;

// 원판 번호
int x; 
// 회전 방향
int d; 
// 회전 횟수
int k;

// 시계 방향 회전
void clockwise(deque<int>& target, int count) {

    for(int i = 0; i < count; i++) {
        target.emplace_front(target.back());
        target.pop_back();
    }
}

// 반시계 방향 회전
void counterClockwise(deque<int>& target, int count) {

    for(int i = 0; i < count; i++) {
        target.emplace_back(target.front());
        target.pop_front();
    }
}

void printMap(vector<deque<int>>& deqTor) {

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {

            cout << deqTor[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int dy[] = {1, -1, 0, 0};
int dx[] = {0, 0, 1, -1};

void checkSameNumber(vector<deque<int>>& deqTor) {

    cout << "=======before=======\n";
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {

            cout << deqTor[i][j] << " ";
        }
        cout << endl;
    }

    bool findSameNumber = false;
    
    bool check[51][51];
    memset(check[0], false, sizeof(check));
    
    double mean = 0;
    int count = 0;

    // 탐색
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {

            if(deqTor[i][j]) {
                mean += deqTor[i][j];
                count++;

                for(int l = 0; l < 4; l++) {

                    int y = i + dy[l];
                    int x = j + dx[l];

                    if(x >= M) x = 0;
                    else if(x < 0) x = M - 1;

                    if(y < 0 || y >= N) continue;

                    if(deqTor[i][j] == deqTor[y][x]) {

                        findSameNumber = true;
                        check[i][j] = true;
                        break;
                    }
                }
            }
        }
    }

    if(findSameNumber) {
        cout << "=======erase=======\n";
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {

                if(check[i][j]) {
                    deqTor[i][j] = 0;
                    continue;
                }
            }
        }
    }
    else {
        mean /= count;
        cout << "=======calc=======\n";
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {

                if(!deqTor[i][j]) continue;

                if(deqTor[i][j] > mean) {
                    deqTor[i][j]--;
                }
                else if(deqTor[i][j] < mean) {
                    deqTor[i][j]++;
                }
            }
        }
    }
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> N >> M >> T;

    vector<deque<int>> deqTor(N);

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {

            int tmp;
            cin >> tmp;
            deqTor[i].emplace_back(tmp);
        }
    }

    for(int i = 0; i < T; i++) {

        cin >> x >> d >> k;
        k %= M;

        int alpha = 1;
        while((x * alpha) <= N) {
            if(d) {
                counterClockwise(deqTor[(x * alpha) - 1], k);
            }
            else {
                clockwise(deqTor[(x * alpha) - 1], k);
            }
            alpha++;
        }
        checkSameNumber(deqTor);
        printMap(deqTor);
    }

    int ans = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            ans += deqTor[i][j];
        }
    }
    cout << ans;
}   