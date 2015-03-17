#include <iostream>
#include <limits>
using namespace std;

int garden[105][105];
bool mark[105][105];

int main() {
	int n, m, k;
	int minsum = 0;
	//in
	cin >> n >> m >> k;
	for (int y = 1; y <= n; ++y){
		for (int x = 1; x <= m; ++x){
			cin >> garden[y][x];
		}
	}
	int x, y;
	for (int i = 0; i < k; ++i){
		cin >> y >> x;
		mark[y][x] = true;
		minsum += garden[y][x];
		garden[y][x] = 0;
	}
	//Border
	for (int i = 0; i <= n + 1; ++i){
		garden[i][0] = std::numeric_limits<int>::max();
		garden[i][m + 1] = std::numeric_limits<int>::max();
	}
	for (int i = 0; i <= m + 1; ++i){
		garden[0][i] = std::numeric_limits<int>::max();
		garden[n + 1][i] = std::numeric_limits<int>::max();
	}
	//calc

	//out
	for (int y = 1; y <= n; ++y){
		for (int x = 1; x <= m; ++x){
			cout << mark[y][x] ? '#' : '.';
		}
		cout << endl;
	}
	return 0;
}
