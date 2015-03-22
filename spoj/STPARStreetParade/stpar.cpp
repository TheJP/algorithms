#include <iostream>
#include <stack>
using namespace std;

int main(void){
	while (true){
		int n;
		int input;
		int anz = 1;
		stack<int> sideway;
		cin >> n;
		if (n == 0){
			return 0;
		}
		for (int i = 1; i <= n; i++){
			cin >> input;
			if (anz != input){
				while (!sideway.empty() && sideway.top() == anz){
					sideway.pop();
					anz++;
				}
				sideway.push(input);
			}
			else{
				anz++;
			}
		}
		while (!sideway.empty() && sideway.top() == anz){
			sideway.pop();
			anz++;
		}
		if (sideway.empty()){
			cout << "yes\n";
		}
		else{
			cout << "no\n";
		}
	}
}
