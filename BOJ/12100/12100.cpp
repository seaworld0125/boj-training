#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

int N;
int ans = 2;

void recursive(int basicMap[][21], int dir, int count) {

    int map[21][21];
    memcpy(map, basicMap, 1764);

    if(count == 5) {
        return;
    }

    if(dir == 0 || dir == 1) { // 왼 방향, 아래 방향
        for(int l = 0; l < N; l++) { 
            
            vector<deque<int>> mem(N);
            for(int k = 0; k < N; k++) { 
                int num = (dir == 0 ? map[l][k] : map[k][l]); 
                
                if(num == 0) continue;

                if(mem[l].size() && mem[l].back() == num) { 
                    mem[l].pop_back();      
                    mem[l].emplace_back(num * 2); 
                    mem[l].emplace_back(0); 
                    ans = max(ans, num * 2);
                }
                else { 
                    mem[l].emplace_back(num);
                }
            }

            int i = 0;
            int size = mem[l].size();
            for(int k = 0; k < size; k++) { 
                int num = mem[l].front();
                mem[l].pop_front();

                if(num == 0) continue;

                if(dir == 0) map[l][i++] = num;
                else map[i++][l] = num;
            }
            for(; i < N; i++) {
                if(dir == 0) map[l][i] = 0;
                else map[i][l] = 0;
            }
        }
    }
    else if(dir == 2 || dir == 3) { // 오른쪽, 위 방향
        for(int l = N - 1; l >= 0; l--) { 
            
            vector<deque<int>> mem(N);
            for(int k = N - 1; k >= 0; k--) {
                int num = (dir == 2 ? map[l][k] : map[k][l]); 
                
                if(num == 0) continue;

                if(mem[l].size() && mem[l].back() == num) {
                    mem[l].pop_back(); 
                    mem[l].emplace_back(num * 2); 
                    mem[l].emplace_back(0);
                    ans = max(ans, num * 2);
                }
                else { 
                    mem[l].emplace_back(num);
                }
            }
            int i = N - 1;
            int size = mem[l].size();
            for(int k = 0; k < size; k++) {
                int num = mem[l].front();
                mem[l].pop_front();

                if(num == 0) continue;

                if(dir == 2) map[l][i--] = num;
                else map[i--][l] = num;
            }
            for(; i >= 0; i--) {
                if(dir == 2) map[l][i] = 0;
                else map[i][l] = 0;
            }
        }
    }

    recursive(map, 0, count + 1);
    recursive(map, 1, count + 1);
    recursive(map, 2, count + 1);
    recursive(map, 3, count + 1);
}

int main() {
    cin >> N;

    int basicMap[21][21];
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> basicMap[i][j];

            ans = max(ans, basicMap[i][j]);
        }        
    }

    recursive(basicMap, 0, 0); // 왼
    recursive(basicMap, 1, 0); // 아
    recursive(basicMap, 2, 0); // 오
    recursive(basicMap, 3, 0); // 위

    cout << ans;
}