#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;

int n;
int input[1001];
int cache[1001][1001];

int getMaxDiff(int left, int right) {
    if (right - left == 1) { return input[left]; }
    if (right - left == 2) { return abs(input[left] - input[left + 1]); }
    if (cache[left][right] >= 0) { return cache[left][right]; }

    bool caseOneLeft = input[left + 1] >= input[right - 1];
    bool caseTwoLeft = input[left] >= input[right - 2];

    int result = max(getMaxDiff(left + (caseOneLeft ? 2 : 1), right - (caseOneLeft ? 0 : 1)) + (input[left] - input[caseOneLeft ? left + 1 : right - 1]),
        getMaxDiff(left + (caseTwoLeft ? 1 : 0), right - (caseTwoLeft ? 1 : 2)) + (input[right - 1] - input[caseTwoLeft ? left : right - 2]));
    cache[left][right] = result;
    return result;
}

int main(void) {
    cin >> n;

    int round = 1;
    while (n > 0)
    {
        for (int i = 0; i < n; ++i) {
            cin >> input[i];
        }

        memset(cache, -1, sizeof(cache));
        cout << "In game " << round << ", the greedy strategy might lose by as many as " << getMaxDiff(0, n) << " points." << endl;

        ++round;
        cin >> n;
    }
    return 0;
}
