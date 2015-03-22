#include <iostream>
using namespace std;

int main(void) {
	int n, a, b;
	cin >> n;
	for (int i = 0; i < n; ++i){
		cin >> a;
		if (a & 1){ cout << a << endl; }
		else {
			b = 0;
			while (a){
				b = (b << 1) | (a & 1);
				a = a >> 1;
			}
			cout << b << endl;
		}
	}
	return 0;
}