#include <iostream>
#include <vector>
using namespace std;

void findPrimeNumber(vector<bool> & list, int N) {
    for(int i = 2; i * i <= N; i++)
        if(list[i])
            for(int j = i * i; j <= N; j += i)
                list[j] = false;
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, ans = 0;
    cin >> N;

    if(N == 1) {
        cout << 0;
        return 0;
    }

    vector<bool> primeList(N + 1, true);
    vector<int> primeNumber;
    
    findPrimeNumber(primeList, N);

    for(int i = 2; i <= N; i++) 
        if(primeList[i])
            primeNumber.emplace_back(i);

    int left = 0, right = 0, sum = primeNumber[0], size = primeNumber.size();

    while(left <= right) {
        if(sum == N) {
            ans++;
        }
        if(sum <= N) {
            if(size <= right + 1) break;
            right++;
            sum += primeNumber[right];
        }
        else if(sum > N) {
            sum -= primeNumber[left];
            left++;
        }
    }
    cout << ans;
}