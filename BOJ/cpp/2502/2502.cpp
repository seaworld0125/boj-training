#include <iostream>
using namespace std;

int D, K;

bool check(int a, int b) {
    int prev = b;
    int next = a + b;
    for(int i = 3; i < D; i++) {
        int tmp = prev;
        prev = next;
        next += tmp;
    }
    if(next == K) {return true;}
    return false;
}

int main() {
    cin >> D >> K;

    int limit = K / (D - 1);

    for(int i = 1; i <= limit * 2; i++) {
        for(int j = 1; j <= limit * 2; j++) {
            if(check(i, j)) {
                cout << i << endl << j;
                return 0;
            }
        }
    }
}