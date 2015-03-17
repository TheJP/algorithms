#include <iostream>
#include <string>
#include <stack>
using namespace std;

#define LINE 400

struct N {
	int l; //Left
	int r; //Right
};

int score[300];
struct N exps[LINE + 5];
string input;

int build_node(int l, int r){
	if (l == r) return l;
	if (r < l) return 0;
	int highest = 0; int index = 0;
	for (int k = l; k < r; ++k){
		if (input[k] == '('){ k = exps[k].r; }
		else if (exps[k].l == 0 && score[input[k]] > highest) {
			highest = score[input[k]];
			index = k;
		}
	}
	if (highest > 0){
		exps[index].l = build_node(l, index - 1);
		exps[index].r = build_node(index + 1, r);
		return index;
	}
	else {
		return l;
	}
}

void printONP(int i){
	char c = input[i];
	if (score[c] > 0){
		printONP(exps[i].l);
		printONP(exps[i].r);
	}
	if (c != '(' && c != ')'){
		cout << c;
	}
}

int main() {
	int i = 0;
	score['^'] = ++i;
	score['/'] = ++i;
	score['*'] = ++i;
	score['-'] = ++i;
	score['+'] = ++i;
	score['('] = ++i;
	int n;
	cin >> n;
	for (i = 0; i < n; ++i){
		cin >> input;
		int m = input.length();
		stack<int> brackets;
		for (int a = 0; a < LINE + 5; ++a){ exps[a].l = 0; exps[a].r = 0; } //reset exps
		for (int j = 0; j < m; ++j){
			if (input[j] == '('){
				brackets.push(j);
			}
			else if (input[j] == ')'){
				int x = brackets.top(); brackets.pop();
				exps[j].l = x;
				exps[x].r = j;
				exps[x].l = build_node(x + 1, j - 1);
			}
		}
		printONP(exps[0].l);
		cout << endl;
	}
	return 0;
}
