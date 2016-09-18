#include <iostream>
#include <algorithm>

using namespace std;

struct block {
    int x, y, z;
    block() {}
    block(int x, int y, int z) { this->x = x; this->y = y; this->z = z; }
};

block blocks[30 * 6 + 1];
int cache[30 * 6 + 1];

int main(void) {
    int n;
    cin >> n;
    while (n > 0) {

        int n2 = n * 6;
        for (int i = 0; i < n2; i += 6) {
            cin >> blocks[i].x >> blocks[i].y >> blocks[i].z;
            block c = blocks[i];
            blocks[i + 1] = block(c.x, c.z, c.y);
            blocks[i + 2] = block(c.y, c.x, c.z);
            blocks[i + 3] = block(c.y, c.z, c.x);
            blocks[i + 4] = block(c.z, c.x, c.y);
            blocks[i + 5] = block(c.z, c.y, c.x);
        }
        sort(blocks, blocks + n2, [](block a, block b) { return a.x < b.x; });

        int result = 0;
        for (int i = 0; i < n2; ++i) {
            int localmax = 0;

            for (int j = i - 1; j >= 0; --j) {
                if (blocks[j].y < blocks[i].y && blocks[j].x < blocks[i].x) {
                    localmax = max(localmax, cache[j]);
                }
            }

            cache[i] = localmax + blocks[i].z;
            result = max(result, cache[i]);
        }

        cout << result << endl;
        cin >> n;
    }

    return 0;
}
