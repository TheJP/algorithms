#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <tuple>

using namespace std;

const int MaxN = 250;
const int N = 250 + 5;
char image[N][N];
int perms[4][2] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };

int main(void) {
	char cmd;
	int x1, x2, y1, y2;
	char color, tmpcolor;
	string name;
    int cols = 0, rows = 0;
    queue<tuple<int, int>> q;
	do {
		cin >> cmd;
		switch (cmd) {
			case 'I':
				cin >> cols >> rows;
				//Create new image initialized with 'O'
                //(Intentional fall through)
			case 'C':
				//Clear current image (= set all pixels to 'O')
                fill(&image[1][0], &image[1][0] + (rows * N), 'O');
				break;
			case 'L':
				cin >> x1 >> y1 >> color;
				//Set pixel at x1,y1 to the given color
                image[y1][x1] = color;
				break;
			case 'V':
				cin >> x1 >> y1 >> y2 >> color;
				//Set the pixels from x1,y1 to x1,y2 to the given color
                for (int y = min(y1, y2); y <= max(y1, y2); ++y) { image[y][x1] = color; }
				break;
			case 'H':
				cin >> x1 >> x2 >> y1 >> color;
				//Set the pixels from x1,y1 to x2,y1 to the given color
                for (int x = min(x1, x2); x <= max(x1, x2); ++x) { image[y1][x] = color; }
				break;
			case 'K':
				cin >> x1 >> y1 >> x2 >> y2 >> color;
				//Set all pixels in the rectangle x1,y1 to x2,y2 to the given color
                for (int y = min(y1, y2); y <= max(y1, y2); ++y) {
                    for (int x = min(x1, x2); x <= max(x1, x2); ++x) {
                        image[y][x] = color;
                    }
                }
				break;
			case 'F':
				cin >> x1 >> y1 >> color;
				//Fill command: Draw every pixel with the same color as the pixel at x1,y1
                //which also has a common edge with the pixel x1,y1 or has a common edge with any pixel which was colored in this step.
                tmpcolor = image[y1][x1];
                if (tmpcolor != color) {
                    q.push(make_tuple(y1, x1));
                    image[y1][x1] = color;
                    while (!q.empty())
                    {
                        tie(y1, x1) = q.front(); q.pop();
                        for (int i = 0; i < 4; ++i) {
                            y2 = y1 + perms[i][0];
                            x2 = x1 + perms[i][1];
                            if (image[y2][x2] == tmpcolor && y2 <= rows && x2 <= cols) {
                                image[y2][x2] = color;
                                q.push(make_tuple(y2, x2));
                            }
                        }
                    }
                }
				break;
			case 'S':
				cin >> name;
				//Print image name and image to cout
                cout << name << endl;
                for (int y = 1; y <= rows; ++y) {
                    for (int x = 1; x <= cols; ++x) {
                        cout << image[y][x];
                    }
                    cout << endl;
                }
				break;
			default:
                getline(cin, name);
				break;
		}
	} while (cmd != 'X');
	return 0;
}