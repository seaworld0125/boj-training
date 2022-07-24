#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
using namespace std;
#define ll long long
/*
    https://school.programmers.co.kr/learn/courses/30/lessons/72414
    
    1차시도 77.4 (1시간 20분)
    2차시도 100 (2시간 5분)
*/
vector<string> split(string str, char Delimiter) {
    istringstream iss(str);             
    string buffer;                      
 
    vector<string> result;
 
    // istringstream은 istream을 상속받으므로 getline을 사용할 수 있다.
    while (getline(iss, buffer, Delimiter)) {
        result.push_back(buffer);               
    }
 
    return result;
}

int timeStringToTimeData(string timeString) {

    auto timePoints = split(timeString, ':');
    return (stoi(timePoints[0]) * 60 * 60)
        + (stoi(timePoints[1]) * 60)
        + stoi(timePoints[2]);
}

string timeDataToTimeString(int time) {

    string hour = "00" + to_string(time / 3600);
    string min = "00" + to_string((time % 3600) / 60);
    string sec = "00" + to_string((time % 3600) % 60);

    hour = hour.substr(hour.size() - 2, 2);
    min = min.substr(min.size() - 2, 2);
    sec = sec.substr(sec.size() - 2, 2);

    return hour + ":" + min + ":" + sec;
}

void timeAcc(vector<int>& history, int& start, int& end) {

    for(int i = start; i < end; i++) {
        history[i]++;
    }
}

string solution(string play_time, string adv_time, vector<string> logs) {
    if(play_time == adv_time) {
        return "00:00:00";
    }

    int totalPlayTime = timeStringToTimeData(play_time);
    int advPlayTime = timeStringToTimeData(adv_time);

    vector<int> history(totalPlayTime + 1, 0);
    vector<ll> prefix(totalPlayTime + 1, 0);

    for(string log : logs) {
        auto splitLogs = split(log, '-');

        int start = timeStringToTimeData(splitLogs[0]);
        int end = timeStringToTimeData(splitLogs[1]);

        timeAcc(history, start, end);
    }

    prefix[0] = history[0];
    for(int i = 1; i <= totalPlayTime; i++) {
        prefix[i] = prefix[i - 1] + history[i];
    }

    ll ans, maxPlayTime = 0;
    int start = 0, end = advPlayTime - 1;
    
    while(end <= totalPlayTime) {
        ll time;
        if(start > 0) {
            if(history[start]) {
                time = prefix[end] - prefix[start - 1];
            }
            else {
                time = prefix[end] - prefix[start];
            }
        }
        else {
            time = prefix[end];
        }
        if(maxPlayTime < time) {
            maxPlayTime = time;
            ans = start;
        }
        start++,
        end++;
    }
    return timeDataToTimeString(ans);
}

int main() {
    vector<string> play_times = {
        "02:03:55",
        "99:59:59",
        "50:00:00",
        "00:00:30",
        "00:00:10"
    };

    vector<string> adv_times = {
        "00:14:15",
        "25:00:00",
        "50:00:00",
        "00:00:15",
        "00:00:05"
    };

    vector<vector<string>> logs = {
        {"01:20:15-01:45:14", "00:40:31-01:00:00", "00:25:50-00:48:29", "01:30:59-01:53:29", "01:37:44-02:02:30"},
        {"69:59:59-89:59:59", "01:00:00-21:00:00", "79:59:59-99:59:59", "11:00:00-31:00:00"},
        {"15:36:51-38:21:49", "10:14:18-15:36:51", "38:21:49-42:51:45"},
        {"00:00:00-00:00:30"},
        {"00:00:07-00:00:10", "00:00:07-00:00:10"},
    };

    for(int i = 0; i < play_times.size(); i++) {

        cout << solution(play_times[i], adv_times[i], logs[i]) << endl;
    }
}