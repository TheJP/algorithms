#include <iostream>
#include <math.h>
using namespace std;

/*#define MAX 1000000010
bool notprim[MAX];


int s1() {
	notprim[1] = true;
	int n;
	int lowest = 2;
	int lo, up, to;
	cin >> n;
	for (int i = 0; i < n; ++i){
		cin >> lo >> up;
		to = ceil(sqrt(up));
		//calc all primes
		while (lowest < to){
			if (!notprim[lowest]){
				for (int j = lowest + lowest; j <= MAX; j += lowest){
					notprim[j] = true;
				}
			}
			++lowest;
		}
		//print results
		for (int j = lo; j <= up; ++j){
			if (!notprim[j]){ cout << j << endl; }
		}
		cout << endl;
	}
	return 0;
}

int s2() {
	notprim[1] = true;
	int n;
	int lowest = 2;
	int lo, up, to;
	cin >> n;
	for (int i = 0; i < n; ++i){
		cin >> lo >> up;
		to = ceil(sqrt(up));
		//calc all primes
		if (lowest < to){
			for (int k = 2; k <= to; ++k){
				if (!notprim[k]){
					for (int j = k + k; j <= up; j += k){
						notprim[j] = true;
					}
				}
			}
			lowest = to;
		}
		//print results
		for (int j = lo; j <= up; ++j){
			if (!notprim[j]){ cout << j << endl; }
		}
		cout << endl;
	}
	return 0;
}

int s3() {
	notprim[1] = true;
	int n;
	cin >> n;
	int * lo = new int[n];
	int * up = new int[n];
	int maxi = 2;
	//in
	for (int i = 0; i < n; ++i){
		cin >> lo[i] >> up[i];
		if (up[i] > maxi){ maxi = up[i]; }
	}
	//calc
	int to = ceil(sqrt(maxi));
	for (int k = 2; k <= to; ++k){
		if (!notprim[k]){
			for (int j = k + k; j <= maxi; j += k){
				notprim[j] = true;
			}
		}
	}
	//out
	for (int i = 0; i < n; ++i){
		for (int j = lo[i]; j <= up[i]; ++j){
			if (!notprim[j]){ cout << j << endl; }
		}
		cout << endl;
	}
	return 0;
}*/

int s4() {
	int n;
	cin >> n;
	int lo, up, to;
	bool prim;
	//in
	for (int i = 0; i < n; ++i){
		cin >> lo >> up;
		if (lo <= 2 && up >= 2){ cout << 2 << endl; }
		if (lo % 2 == 0){ ++lo; }
		if (lo == 1){ lo = 3; }
		for (; lo <= up; lo += 2){
			prim = true;
			to = ceil(sqrt(lo));
			for (int x = 3; prim && x <= to; x += 2){
				if (lo % x == 0){ prim = false; }
			}
			if (prim){ cout << lo << endl; }
		}
		cout << endl;
	}
	return 0;
}

int main() {
	return s4();
}