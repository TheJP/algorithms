#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 1000000;
int result[MAX + 3];

int calc(int n) {
	if (n > MAX || result[n] == 0) {
		int tmp = (n % 2 == 0 ? calc(n / 2) : calc(n * 3 + 1)) + 1;
		if (n <= MAX) { result[n] = tmp; }
		else { return tmp; }
	}
	return result[n];
}

int main(void) {
	for (int r = 1, a = 1; a <= MAX; ++r, a *= 2) {
		result[a] = r;
	}

	int a, b, x, y, maxn;

	while (cin >> a >> b) {
		x = min(a, b);
		y = max(a, b);
		maxn = 0;
		for (int i = x; i <= y; ++i) { maxn = max(maxn, calc(i)); }
		cout << a << ' ' << b << ' ' << maxn << endl;
	}

	return 0;
}