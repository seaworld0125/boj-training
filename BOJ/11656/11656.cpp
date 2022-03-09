#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define endl '\n'

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    // input
    string str;
    cin >> str;

    int strLen = str.length();

    // create suffix array
    vector<string> suffixArr;
    for(int i = 0; i < strLen; i++)
        suffixArr.emplace_back(str.substr(i, strLen - i));

    // sorting
    sort(suffixArr.begin(), suffixArr.end());

    // print
    for(string s : suffixArr)
        cout << s << endl;
}