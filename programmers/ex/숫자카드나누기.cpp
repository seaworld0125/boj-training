#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int check(int ans, vector<int> &array) {
    for(int &n : array) {
        if(n % ans == 0) return 0;
    }
    return ans;
}

int solution(vector<int> arrayA, vector<int> arrayB) {

    sort(arrayA.begin(), arrayA.end(), less<int>());
    sort(arrayB.begin(), arrayB.end(), less<int>());

    int gcdA = arrayA[0];
    int size = arrayA.size();

    for(int i = 1; i < size; i++) {
        gcdA = gcd(gcdA, arrayA[i]);
    }

    int gcdB = arrayB[0];
    size = arrayB.size();

    for(int i = 1; i < size; i++) {
        gcdB = gcd(gcdB, arrayB[i]);
    }

    if(gcdA == gcdB) return 0;

    if(gcdA > gcdB) return check(gcdA, arrayB);
    else return check(gcdB, arrayA);
}