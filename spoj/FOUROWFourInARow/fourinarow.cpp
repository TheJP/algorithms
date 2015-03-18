#include <iostream>
#include <deque>
using namespace std;

int main() {
	int n;
	char c;
	int x;
	bool turn;
	cin >> n;
	deque<bool> cols[8];
	for (int i = 1; i <= n; ++i){
		for (int j = 1; j <= 7; ++j){
			cols[j].clear();
		}
		do {
			cin >> c;
		} while (c != ':');
		getchar(); //get rid of space
		turn = false;
		do {
			c = getchar();
			if (c < '0' || c > '9'){ cout << "Game #" << i << " is not over, yet." << endl; break; }
			x = c - '0';
			if (cols[x].size() == 6){ cout << "Game #" << i << " is invalid." << endl; break; }
			cols[x].push_back(turn);
			int colsx_size = cols[x].size();
			//** Find winner **//
			// <->
			int plus = 0; int minus = 0;
			for (int j = 0; j <= 7; ++j){
				if (x - j >= 1 && cols[x - j].size() >= cols[x].size() && cols[x - j][colsx_size - 1] == turn){
					++minus;
				} else { break; }
			}
			for (int j = 1; j <= 7; ++j){
				if (x + j <= 7 && cols[x + j].size() >= colsx_size && cols[x + j][colsx_size - 1] == turn){
					++plus;
				} else { break; }
			}
			//^v
			int vert = 0;
			for (int j = colsx_size - 1; j >= 0; --j){
				if (cols[x][j] == turn){
					++vert;
				} else { break; }
			}
			//Diagonal
			int d1plus = 0, d1minus = 0; // / (plus ^, minus v)
			int d2plus = 0, d2minus = 0; // \ (plus ^, minus v)
			for (int j = 0; j <= 7; ++j){
				if (d1plus >= 0){
					if (colsx_size + j < 6 && x + j <= 7 && cols[x + j].size() >= colsx_size + j && cols[x + j][colsx_size + j - 1] == turn){ ++d1plus; }
					else { d1plus *= -1; }
				}
				if (d1minus >= 0){
					if (colsx_size - j > 0 && x - j > 0 && cols[x - j].size() >= colsx_size - j && cols[x - j][colsx_size - j - 1] == turn){ ++d1minus; }
					else { d1minus *= -1; }
				}
				if (d2plus >= 0){
					if (colsx_size + j < 6 && x - j > 0 && cols[x - j].size() >= colsx_size + j && cols[x - j][colsx_size + j - 1] == turn){ ++d2plus; }
					else { d2plus *= -1; }
				}
				if (d2minus >= 0){
					if (colsx_size - j > 0 && x + j <= 7 && cols[x + j].size() >= colsx_size - j && cols[x + j][colsx_size - j - 1] == turn){ ++d2minus; }
					else { d2minus *= -1; }
				}
			}
			d1plus *= -1; d1minus *= -1; --d1minus;
			d2plus *= -1; d2minus *= -1; --d2minus;
			//** Check for winner / print winning **//
			if (plus + minus >= 4 || vert >= 4 || d1plus + d1minus >= 4 || d2plus + d2minus >= 4){
				//Found winner:
				//1. Are there more moves -> invalid
				c = getchar();
				if (c >= '0' && c <= '9'){ cout << "Game #" << i << " is invalid." << endl; break; }
				//2. Print win
				cout << "Game #" << i << " is over. The " << (turn ? "second" : "first") << " player won." << endl;
				//3. Print board (capital X, O for winning spots!)
				cout << "-------" << endl;
				int maxx = 0; for (int j = 1; j <= 7; ++j){ if (cols[j].size() > maxx){ maxx = cols[j].size(); } }
				char * output[8]; for (int j = 1; j <= 7; ++j){ output[j] = new char[6]; }
				//Fill grid with lower case
				for (int row = maxx - 1; row >= 0; --row){
					for (int col = 1; col <= 7; ++col){
						if (row < cols[col].size()){ output[col][row] = cols[col][row] ? 'o' : 'x'; }
						else { output[col][row] = ' '; }
					}
				}
				//Fill gird with upper case
				//<->
				if (plus + minus >= 4){
					for (int j = 0; j < minus; ++j){ output[x - j][colsx_size - 1] = turn ? 'O' : 'X'; }
					for (int j = 1; j <= plus; ++j){ output[x + j][colsx_size - 1] = turn ? 'O' : 'X'; }
				}
				//^v
				if (vert >= 4){
					for (int j = 1; j <= vert; ++j){ output[x][colsx_size - j] = turn ? 'O' : 'X'; }
				}
				//Diagonal
				if (d1minus + d1plus >= 4){ // / (plus ^, minus v)
					for (int j = 0; j <= 7; ++j){
						if (j < d1plus){ output[x + j][colsx_size + j - 1] = turn ? 'O' : 'X'; }
						if (j <= d1minus){ output[x - j][colsx_size - j - 1] = turn ? 'O' : 'X'; }
					}
				}
				if (d2minus + d2plus >= 4){ // \ (plus ^, minus v)
					for (int j = 0; j <= 7; ++j){
						if (j < d2plus){ output[x - j][colsx_size + j - 1] = turn ? 'O' : 'X'; }
						if (j <= d2minus){ output[x + j][colsx_size - j - 1] = turn ? 'O' : 'X'; }
					}
				}
				//Output char array
				for (int row = maxx - 1; row >= 0; --row){
					for (int col = 1; col <= 7; ++col){
						cout << output[col][row];
					}
					cout << endl;
				}
				//Delete char array
				for (int j = 1; j <= 7; ++j){ delete[] output[j]; }
				cout << "-------" << endl;
				break;
			}
			//** Check for filled board **//
			bool full = true;
			for (int j = 1; j <= 7; ++j){
				if (cols[j].size() < 6){ full = false; }
			}
			if (full){ cout << "Game #" << i << " is over. There is no winner." << endl; break; }
			turn = !turn;
		} while (true);
	}
	return 0;
}
