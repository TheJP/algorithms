#include <iostream>
#include <string>
#include <limits>

using namespace std;

const int MAX = 100;
const int ARR = MAX + 5;
int star = numeric_limits<int>::min();

void inc(int (&f)[ARR][ARR], int x, int y) {
	for (int a = y - 1; a <= y + 1; ++a) {
		for (int b = x - 1; b <= x + 1; ++b) {
			++f[a][b];
		}
	}
}

int main(void) {
	int rows, cols;
	int field = 0;
	string line;
	cin >> rows >> cols;
	while (rows != 0 && cols != 0) {
		if (field != 0) { cout << endl; }
		int f[ARR][ARR] = {{0}};
		for (int y = 1; y <= rows; ++y) {
			cin >> line;
			for (int x = 1; x <= cols; ++x) {
				if (line[x - 1] == '*') { inc(f, x, y); f[y][x] = star; }
			}
		}
		cout << "Field #" << (++field) << ':' << endl;
		for (int y = 1; y <= rows; ++y) {
			for (int x = 1; x <= cols; ++x) {
				if (f[y][x] < 0) { cout << '*'; }
				else { cout << f[y][x]; }
			}
			cout << endl;
		}
		cin >> rows >> cols;
	}
	return 0;
}