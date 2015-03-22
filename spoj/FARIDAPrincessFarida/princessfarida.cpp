#include <iostream>
#include <algorithm>
using namespace std;

unsigned int mon[10005];
unsigned long long int sol[10005];

int main() {
	int n, m;
	unsigned long long int output;
	cin >> n;
	for (int i = 1; i <= n; ++i){
		cin >> m;
		for (int j = 0; j < m; ++j){
			cin >> mon[j];
		}
		output = 0;
		for (int j = m - 1; j >= 0; --j){
			if (j + 1 == m || j + 2 == m){ sol[j] = mon[j]; }
			else if (j + 3 == m){ sol[j] = mon[j] + sol[j + 2]; }
			else { sol[j] = mon[j] + max(sol[j + 2], sol[j + 3]); }
			output = max(output, sol[j]);
		}
		cout << "Case " << i << ": " << output << endl;
	}
	return 0;
}
