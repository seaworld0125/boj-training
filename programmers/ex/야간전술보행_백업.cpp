#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Data {
    int officeHour;
    int restHour;
    int scopeStart;
    int scopeEnd;

    Data(int a, int b, int c, int d) {
        if(c < d) {
            scopeStart = c;
            scopeEnd = d;
        }
        else {
            scopeStart = d;
            scopeEnd = c;
        }
        officeHour = a;
        restHour = b;
    }
};

int solution(int distance, vector<vector<int>> scope, vector<vector<int>> times) {
    int answer = 0;
    int size = scope.size();

    vector<Data> datas;

    for(int i = 0; i < size; i++) {
        datas.emplace_back(times[i][0], times[i][1], scope[i][0], scope[i][1]);
    }

    // sort vector of vector
    sort(datas.begin(), datas.end(), [](Data& a, Data& b) {
        return a.scopeStart < b.scopeStart;
    });

    for(auto data: datas) {
        printf("[[%d %d], [%d %d]]\n", data.scopeStart, data.scopeEnd, data.officeHour, data.restHour);
    }

    for(int i = 1; i <= distance; i++) {
        for(auto data: datas) {
            if(data.scopeStart <= i && i <= data.scopeEnd) {
                if(((i - 1) % (data.officeHour + data.restHour)) < data.officeHour) {
                    printf("i: %d\n", i);
                    printf("(%d) % (%d) < %d\n", i, (data.officeHour + data.restHour), data.officeHour);
                    return i;
                }
            }
        }
    }
    return distance;
}

int main() {
    // printf("%d\n", solution(100, {{3, 4}, {5, 6}, {7, 8}}, {{2, 2}, {4, 4}, {6, 6}}));

    cout << (6 % 7);
}