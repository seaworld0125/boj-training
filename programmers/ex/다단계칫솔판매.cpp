#include <string>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

unordered_map<string, int> memberNum; 

struct Member {
    string ref;
    int profit;

    Member(string ref): ref(ref), profit(0) {}

    void createRevenue(int revenue, vector<Member>& memberList) {
        if((double) revenue * 0.1 < 1.0) {
            profit += revenue;
            return;
        }

        int portion = revenue * 0.1;
        profit += (revenue - portion);

        if(ref != "-") {
            int idx = memberNum[ref];
            memberList[idx].createRevenue(portion, memberList);
        }
    }
};

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    vector<int> answer;
    vector<Member> memberList;

    int size = enroll.size();

    for(int i = 0; i < size; i++) {
        memberNum[enroll[i]] = i;
        memberList.emplace_back(referral[i]);
    }

    size = seller.size();

    for(int i = 0; i < size; i++) {
        memberList[memberNum[seller[i]]].createRevenue(amount[i] * 100, memberList);
    }

    for(auto &member : memberList) {
        answer.push_back(member.profit);
    }

    return answer;
}