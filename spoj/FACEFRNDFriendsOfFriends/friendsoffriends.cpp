#include <iostream>
using namespace std;

int f[10000];

int main() {
	int n, m;
	int id, id2;
	cin >> n;
	for (int i = 0; i < n; ++i){
		cin >> id >> m;
		if (f[id] < 2){ f[id] = 2; }
		for (int j = 0; j < m; ++j){
			cin >> id2;
			if (f[id2] < 1){ f[id2] = 1; }
		}
	}
	int result = 0;
	for (int i = 0; i <= 9999; ++i){
		if (f[i] == 1){ ++result; }
	}
	cout << result << endl;
	return 0;
}
