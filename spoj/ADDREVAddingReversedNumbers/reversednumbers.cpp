#include <iostream>

using namespace std;

int reverse(int x) {
    int y = 0;
    while (x % 10 == 0 && x > 0) { x /= 10; }
    while (x > 0) {
        y *= 10;
        y += x % 10;
        x /= 10;
    }
    return y;
}

int main(void) {
    int n, a, b;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
        cout << reverse(reverse(a) + reverse(b)) << endl;
    }

    return 0;
}
