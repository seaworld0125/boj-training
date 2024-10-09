#include <cstdio>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);

    for(int i = 0; i < T; i++) {
        long long x, y;
        scanf("%lld %lld", &x, &y);

        if(y - x <= 3) {
            printf("%lld\n", y - x);
            continue;
        }
        else if(y - x == 4) {
            printf("3\n");
            continue;
        }

        int t = 1;
        long long s = 2;

        while(1) {
            if(s + x == y) {
                printf("%d\n", t * 2);
                break;
            }
            else if(s + x - 1 == y) {
                printf("%d\n", t * 2);
                break;
            }
            else if(s + x + 1 == y) {
                printf("%d\n", (t * 2) + 1);
                break;
            }
            t++;
            s += t * 2;
        }
    }
}