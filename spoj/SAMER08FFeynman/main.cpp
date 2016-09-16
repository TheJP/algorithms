#include <iostream>
using namespace std;

int cache[101];

int main(void) {
    //Bottom up
    for (int i = 1; i <= 100; ++i) {
        cache[i] = cache[i - 1] + i * i;
    }

    int n;
    cin >> n;
    while (n > 0)
    {
        cout << cache[n] << endl;
        cin >> n;
    }
    return 0;
}