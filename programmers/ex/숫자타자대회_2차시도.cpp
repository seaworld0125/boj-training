#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

#define INF (int)1e9

int dp[100001][12][12];

unordered_map<char, int> idx = {
    {'1', 0}, {'2', 1}, {'3', 2},
    {'4', 3}, {'5', 4}, {'6', 5},
    {'7', 6}, {'8', 7}, {'9', 8},
    {'*', 9}, {'0', 10}, {'#', 11},
};

unordered_map<char, pair<int, int>> pad = {
    {'1', {0, 0}}, {'2', {0, 1}}, {'3', {0, 2}},
    {'4', {1, 0}}, {'5', {1, 1}}, {'6', {1, 2}},
    {'7', {2, 0}}, {'8', {2, 1}}, {'9', {2, 2}},
    {'*', {3, 0}}, {'0', {3, 1}}, {'#', {3, 2}}
};

int getDist(char a, char b) {
    auto aPos = pad[a];
    auto bPos = pad[b];

    int dy = abs(aPos.first - bPos.first);
    int dx = abs(aPos.second - bPos.second);

    return (2 * abs(dy - dx)) + (3 * (dy < dx ? dy : dx));
}

int solve(string &numbers, int i, char a, char b) {

    if(i == numbers.length()) return 0;
    if(dp[i][idx[a]][idx[b]] != -1) return dp[i][idx[a]][idx[b]];  

    if(numbers[i] == a || numbers[i] == b) {
        return dp[i][idx[a]][idx[b]] = solve(numbers, i + 1, a, b) + 1;
    }
    
    return dp[i][idx[a]][idx[b]] = min(
        solve(numbers, i + 1, numbers[i], b) + getDist(a, numbers[i]),
        solve(numbers, i + 1, a, numbers[i]) + getDist(b, numbers[i])
    );
}

int solution(string numbers) {

    fill_n(dp[0][0], 100001 * 12 * 12, -1);

    return solve(numbers, 0, '4', '6');
}