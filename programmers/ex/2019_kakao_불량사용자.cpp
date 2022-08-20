#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
using namespace std;

// 더 간단한 로직으로 다시 풀기

int BAN_SIZE;
set<string> bucket;
set<string> res;

bool checkSameStr(string& u, string& b) {
    for(int i = 0; i < u.length(); i++) {
        if(u[i] == b[i] || b[i] == '*') continue;
        return false; 
    }
    return true;
}

void findBadId(vector<string>& uid, vector<string>& bid, vector<vector<string>>& bad_id) {
    int uSize = uid.size();
    int bSize = bid.size();

    for(int i = 0; i < uSize; i++) {
        for(int j = 0; j < bSize; j++) {

            if(uid[i].length() != bid[j].length()) continue;
            if(checkSameStr(uid[i], bid[j])) {
                bad_id[j].emplace_back(uid[i]);
            }
        }
    }
}

void findAns(vector<vector<string>>& bad_id, int idx) {
    if(idx == bad_id.size()) {
        if(bucket.size() == BAN_SIZE) {
            string tmp = "";
            for(auto s : bucket) {
                tmp += s;
            }
            res.emplace(tmp);
        } 
        return;
    }

    for(int i = 0; i < bad_id[idx].size(); i++) {
        auto now = bad_id[idx][i];
        if(bucket.find(now) != bucket.end()) continue;

        bucket.emplace(now);
        findAns(bad_id, idx + 1);
        bucket.erase(now);
    }
}

int solution(vector<string> user_id, vector<string> banned_id) {
    BAN_SIZE = banned_id.size();
    vector<vector<string>> bad_id(BAN_SIZE);
    findBadId(user_id, banned_id, bad_id);
    findAns(bad_id, 0);

    return res.size();
}

int main() {
}