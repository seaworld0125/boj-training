#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Tree {
    int age;
    bool dead;
    
    Tree(int a, int d) : age(a), dead(d) {}
};

struct SoilData {
    int y;
    int x;
    int nourishing;
    vector<Tree> trees;

    void addTree(int a = 1) {
        trees.emplace_back(a, 0);
    }    
};

int N, M, K;
int A[11][11];
SoilData map[11][11];

// 12시 방향부터 시계 방향으로...
int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};

void springToSummer(SoilData& soilData) {
    auto& trees = soilData.trees;
    auto& nourishing = soilData.nourishing;

    sort(trees.begin(), trees.end(), [](Tree& a, Tree& b) {
        // 나무가 죽었을 경우, dead value는 true(==1)이다. 즉 false 보다 크기 때문에 오름차순으로 정렬하는 경우 죽은 나무만 뒤로 정렬할 수 있다.
        if(a.dead < b.dead) return true; 
        return a.age < b.age;
    });

    // spring
    for(auto it = trees.begin(); it != trees.end(); it++) {
        auto& tree = *it;

        if(nourishing < tree.age) {
            // cout << "dead!\n";
            tree.dead = true;
        }
        else {
            // cout << "get age!\n";
            nourishing -= tree.age;
            tree.age++;
        }
    }

    // sort and find dead tree start pos
    vector<Tree>::iterator start = trees.end();
    for(auto it = trees.begin(); it != trees.end(); it++) {
        if((*it).dead) {
            start = it;
            break;
        }
    }

    // summer
    for(auto it = start; it != trees.end(); it++) {
        nourishing += ((*it).age / 2);
    }
    trees.erase(start, trees.end());
}
void fall(SoilData& soilData) {
    auto& trees = soilData.trees;
    auto& x = soilData.x;
    auto& y = soilData.y;

    for(auto tree : trees) {
        if(tree.age % 5) continue;

        for(int i = 0; i < 8; i++) {

            int ny = y + dy[i];
            int nx = x + dx[i];

            if(ny < 0 || nx < 0 || ny >= N || nx >= N) continue;

            map[ny][nx].addTree();
        }
    }
}

int main() {ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> N >> M >> K;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> A[i][j];

            map[i][j].nourishing = 5;
            map[i][j].y = i;
            map[i][j].x = j;
        }
    }

    int x, y, a;

    for(int i = 0; i < M; i++) {
        cin >> x >> y >> a;
        x--;
        y--;

        map[x][y].addTree(a);
    }

    while(K--) {
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                // 봄 ~ 여름
                if(map[i][j].trees.size())
                    springToSummer(map[i][j]);
            }
        }
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                // 가을
                if(map[i][j].trees.size())
                    fall(map[i][j]);

                // 양분 주기
                map[i][j].nourishing += A[i][j];
            }
        }
    }

    int ans = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            ans += map[i][j].trees.size();
        }
    }
    cout << ans;
}