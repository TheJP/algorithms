#include <iostream>
#include <string>
#include <math.h>
using namespace std;

int main() {
	int n, m, c;
	cin >> n;
	string s, o;
	for (int i = 0; i < n; ++i){
		cin >> s;
		m = s.length();
		c = m / 2;
		c += m % 2;
		o = string(m, '0');
		for (int j = 0; j < c; ++j){
			o[j] = s[j];
			o[m - j - 1] = s[j];
		}
		bool bigger = false;
		for (int j = c; j < m; ++j){
			if (o[j] > s[j]){ bigger = true; break; }
			else if (o[j] < s[j]){ bigger = false; break; }
		}
		if (!bigger){
			int j = c - 1;
			bool go = true;
			bool overflow = false;
			while (go){
				if (j < 0){ overflow = true; go = false; }
				else {
					if (o[j] == '9'){ o[j] = '0'; o[m - j - 1] = '0'; }
					else { ++o[j]; if (j != c - 1 || m % 2 == 0){ ++o[m - j - 1]; } go = false; }
					--j;
				}
			}
			if (overflow){
				o = string(m + 1, '0');
				o[0] = '1'; o[m] = '1';
			}
		}
		cout << o << endl;
	}
	// your code goes here
	return 0;
}