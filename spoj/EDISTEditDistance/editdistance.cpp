#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include <cstring>

using namespace std;

const int Max = 2000;
int cache[Max + 1][Max + 1];
string a, b;

int distance(int x, int y) {
    if (min(x, y) < 0) { return max(x, y) + 1; }
    if (cache[y][x] > 0) { return cache[y][x]; }
    bool same = a[x] == b[y];
    int result = min(
        distance(x - 1, y - 1) + (same ? 0 : 1),
        min(distance(x - 1, y) + 1, distance(x, y - 1) + 1)
    );
    cache[y][x] = result;
    return result;
}

int main(void) {
    int n;

    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
        cout << distance(a.length() - 1, b.length() - 1) << endl;
        memset(cache, 0, sizeof(cache));
    }

    return 0;
}
