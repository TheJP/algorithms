#include <iostream>
using namespace std;

int main() {
	int n, o;
	cin >> n;
	while (n){
		if (n <= 1){ cout << 5 << endl; }
		else {
			o = (5 * n)
				+ (2 + 3 * n)*(n - 1)
				- 3 * ((n*(n + 1)) / 2 - 1);
			cout << o << endl;
		}
		cin >> n;
	}
	return 0;
}