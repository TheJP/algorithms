#include <iostream>
#include <algorithm>

using namespace std;

int n;
int input[2001];
int cache[2001][2001];

int getMaxProfit(int left, int right, int age) {
    if (right - left == 1) { return input[left] * age; }

    if (cache[left][right] <= 0) {
        cache[left][right] = max(getMaxProfit(left + 1, right, age + 1) + input[left] * age,
            getMaxProfit(left, right - 1, age + 1) + input[right - 1] * age);
    }
    return cache[left][right];;
}

int main(void) {
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> input[i];
    }

    cout << getMaxProfit(0, n, 1) << endl;

    return 0;
}
