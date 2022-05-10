#include "allHeader.h"
using namespace std;

int main() {

    vector<int> lis;
    lis.emplace_back(0);
    lis.emplace_back(1);

    cout << lower_bound(lis.begin(), lis.end(), 2) - lis.begin();
}