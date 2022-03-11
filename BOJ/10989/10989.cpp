#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    // input
    int arr[10001] = {0};
    int N, num;
    scanf("%d", &N);

    for(int i = 0; i < N; i++) {
        scanf("%d", &num);
        arr[num]++;
    }

    // solve
    for(int i = 1; i < 10001; i++)
        for(int j = 0; j < arr[i]; j++)
            printf("%d\n", i);
}