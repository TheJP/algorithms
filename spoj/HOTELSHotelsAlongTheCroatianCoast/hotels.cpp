#include <iostream>
#include <algorithm>

using namespace std;

int houses[300001];

int main(void) {
    int n, target;

    cin >> n >> target;

    int last = 0;
    int sum = 0;
    int best = 0;

    for (int i = 0; i < n; ++i) {
        cin >> houses[i];
        sum += houses[i];
        while (sum > target)
        {
            sum -= houses[last];
            ++last;
        }
        best = max(best, sum);
    }

    cout << best << endl;

    return 0;
}
