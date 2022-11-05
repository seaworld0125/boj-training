#include <string>
#include <vector>

#define ll long long

using namespace std;

ll solution(int n, int m, int x, int y, vector<vector<int>> queries) { // x가 행, y가 열
    ll x1 = x,
        x2 = x,
        y1 = y,
        y2 = y;

    int size = queries.size();
    int dir, dist;
    
    for(int i = size - 1; i >= 0; i--) {

        dir = queries[i][0];
        dist = queries[i][1];

        switch (dir)
        {
        case 0:
            y2 += dist;
            if(y2 >= m) y2 = m - 1;
            if(y1 != 0) y1 += dist;
            break;
        case 1:
            y1 -= dist;
            if(y1 < 0) y1 = 0;
            if(y2 != m - 1) y2 -= dist;
            break;
        case 2:
            x2 += dist;
            if(x2 >= n) x2 = n - 1;
            if(x1 != 0) x1 += dist;
            break;
        case 3:
            x1 -= dist;
            if(x1 < 0) x1 = 0;
            if(x2 != n - 1) x2 -= dist;
            break;
        }
        if(y2 < 0 || y1 >= m || x2 < 0 || x1 >= n) return 0;
    }
    return (y2 - y1 + 1) * (x2 - x1 + 1);
}