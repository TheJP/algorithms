#include <iostream>
#include <vector>
#include <stack>
#include <tuple>
using namespace std;

bool visited[10005];

int main() {
	int n, m;
	cin >> n >> m;
	int x, y;
	vector<int> * g = new vector<int>[n+5];
	for (int i = 0; i < m; ++i){
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	tuple<int, int> t(1, 1), t2(0, 0); //node, previous node
	stack<tuple<int, int>> s;
	s.push(t);
	bool isTree = true;
	while (isTree && !s.empty()){
		t = s.top(); s.pop();
		if (visited[get<0>(t)]){ isTree = false; }
		else {
			visited[get<0>(t)] = true;
			for (int i = g[get<0>(t)].size() - 1; i >= 0; --i){
				int c = g[get<0>(t)][i];
				if (c != get<1>(t)){
					get<0>(t2) = c;
					get<1>(t2) = get<0>(t);
					s.push(t2);
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i){
		if (!visited[i]){ isTree = false; } //Not connected graph
	}
	cout << (isTree ? "YES" : "NO") << endl;
	delete[] g;
	return 0;
}