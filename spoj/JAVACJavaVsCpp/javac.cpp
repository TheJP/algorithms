#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

#define ST_FIRST 0
#define ST_OTHER 2


int main(void){
	int len, i, j, state = ST_FIRST;
	bool cpp = true, java = true;
	string input, output;
	output.reserve(250);
	//scanf("%s", input);
	while (getline(cin, input)){
		output.clear();
		len = input.length();
		if (input[len - 1] != '_'){
			for (i = 0, j = 0; i<len; i++, j++){
				//Range check
				/*if((input[i] < 'A' || (input[i] > 'Z' && input[i] < 'a') || input[i] > 'z') && input[i] != '_'){
				cpp = false; java = false; break;
				}*/
				if (state == ST_OTHER){
					if (input[i] == '_'){
						java = false;
						if (cpp){
							state = ST_FIRST;
							j--;
						}
						else{
							break;
						}
					}
					else if (input[i] <= 'Z'){//is upper?
						cpp = false;
						if (java){
							output.push_back('_');
							output.push_back(input[i] + 32);
						}
						else{
							break;
						}
					}
					else{
						output.push_back(input[i]);
					}
				}
				else if (input[i] < 'a' || input[i] > 'z'){
					cpp = false; java = false; break;
				}
				else{
					state = ST_OTHER;
					if (cpp && !java){
						output.push_back(input[i] - 32);
					}
					else{
						output.push_back(input[i]);
					}
				}
			}
			if (!java & !cpp){
				printf("Error!\n");
			}
			else if (java == cpp){
				cout << input << endl;
			}
			else{
				cout << output << endl;
			}
		}
		else{
			printf("Error!\n");
		}
		cpp = true; java = true; state = ST_FIRST;
		//scanf("%s", input);
	}
	return 0;
}