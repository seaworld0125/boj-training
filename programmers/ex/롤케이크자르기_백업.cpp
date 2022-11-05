#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

struct MYSET {
    set<int> base;
    int counter[10001] = {0};

    MYSET(vector<int>& topping) {

        for(auto t : topping) {
            counter[t]++;
            base.insert(t);
        }
    }

    void erase(int& num) {
        if(counter[num] >= 1) {
            counter[num]--;
        }
        if(counter[num] == 0) {
            base.erase(num);
        }
    }

    int size() {
        return base.size();
    }
};

int solution(vector<int> topping) {

    int ans = 0;
    int size = topping.size();

    if(topping.size() == 1) {
        return ans;
    }

    set<int> a;
    MYSET baseSet(topping);

    for(int i = 0; i < topping.size(); i++) {
        baseSet.erase(topping[i]);
        a.insert(topping[i]);

        if(baseSet.size() == a.size()) {
            ans++;
        }
    }
    return ans;
}

int main() {
    cout << solution({1, 2, 1, 3, 1, 4, 1, 2});
}