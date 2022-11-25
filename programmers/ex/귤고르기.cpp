#include <vector>
#include <algorithm>
using namespace std;

int solution(int k, vector<int> tangerine) {
    struct Data {
        int count;
        int size;
    };
    vector<Data> datas;

    sort(tangerine.begin(), tangerine.end());

    int prev = 0;

    for(int& size : tangerine) {
        if(prev != size) {
            prev = size;
            datas.push_back({1, size}); 
        }
        else {
            datas.back().count++;
        }
    }

    sort(datas.begin(), datas.end(), [](Data& a, Data& b) {
        return a.count > b.count;
    });

    int answer = 0;
    int count = 0;

    for(Data& data : datas) {
        if(count + data.count >= k) {
            answer++;
            break;
        }
        else {
            answer++;
            count += data.count;
        }
    }
    return answer;
}