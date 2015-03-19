#include <iostream>
#include <string>
#include <limits>
#include <stack>
#include <tuple>
using namespace std;

int field[190][190];
int perm[4][2][2] = {
	{ { -1,   0 }, {  0,  1 } }, //up-right
	{ {  0,   1 }, {  1,  0 } }, //right-down
	{ {  1,   0 }, {  0, -1 } }, //down-left
	{ {  0,  -1 }, { -1,  0 } }, //left-up
};

int main() {
	int n;
	cin >> n;
	int cols, rows;
	stack<tuple<int, int, int, int>> s; //y,x,value,direction
	tuple<int, int, int, int> t, t2;
	for (int i = 0; i < n; ++i){
		cin >> rows >> cols;
		//reset
		for (int y = rows; y > 0; --y){
			for (int x = cols; x > 0; --x){
				field[y][x] = std::numeric_limits<int>::max();
			}
		}
		//in, calc
		for (int y = 1; y <= rows; ++y){
			string line;
			cin >> line;
			for (int x = 1; x <= cols; ++x){
				if (line[x - 1] == '1'){
					field[y][x] = 0;
					get<2>(t) = 1;
					for (int p = 0; p < 4; ++p){
						get<0>(t) = y + perm[p][0][0];
						get<1>(t) = x + perm[p][0][1];
						get<3>(t) = p;
						s.push(t);
					}
					while (!s.empty()){
						t = s.top(); s.pop();
						if (get<2>(t) < field[get<0>(t)][get<1>(t)]){
							field[get<0>(t)][get<1>(t)] = get<2>(t);
							get<2>(t2) = get<2>(t) + 1;
							get<3>(t2) = get<3>(t);
							for (int a = 0; a < 2; ++a){
								get<0>(t2) = get<0>(t) + perm[get<3>(t)][a][0];
								get<1>(t2) = get<1>(t) + perm[get<3>(t)][a][1];
								s.push(t2);
							}
						}
					}
				}
			}
		}
		//out
		for (int y = 1; y <= rows; ++y){
			for (int x = 1; x <= cols; x++){
				cout << field[y][x] << (x < cols ? " " : "");
			}
			cout << endl;
		}
	}
	return 0;
}
