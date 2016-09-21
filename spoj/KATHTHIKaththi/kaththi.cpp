#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cstring>
#include <unordered_set>
#include <utility>
#include <functional>

using namespace std;

typedef vector<unordered_set<int>> graph;

string map[1001];
int labels[1001][1001];
int cost[1000001];
graph g;
const int permutations[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

struct point {
    int x, y;
    point() {}
    point(int x, int y) { this->x = x; this->y = y; }
};

//Finding shortest path from 0 to target
int dijkstra(int target) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue;
    queue.push(pair<int, int>(0, 0));
    while (!queue.empty())
    {
        pair<int, int> current = queue.top(); queue.pop();
        if (current.first < cost[current.second]) {
            cost[current.second] = current.first;
            if (current.second == target) { return current.first; }
            for (auto itr = g[current.second].begin(); itr != g[current.second].end(); ++itr) {
                if (current.first + 1 < cost[*itr]) {
                    queue.push(pair<int, int>(current.first + 1, *itr));
                }
            }
        }
    }
    return -1; //Target not reachable
}

int main(void) {
    int n, rows, cols;
    cin >> n;

    for (int i = 0; i < n; ++i) {

        //Input
        cin >> rows >> cols;
        for (int y = 0; y < rows; ++y) {
            cin >> map[y];
        }

        //Putput
        //Creat graph
        int label = 0;
        g = graph();
        memset(labels, -1, sizeof(labels));
        fill_n(cost, 1000001, 5000);
        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {

                //BFS to color each region
                if (labels[y][x] < 0) {
                    g.push_back(unordered_set<int>());
                    queue<point> s;
                    s.push(point(x, y));
                    while (!s.empty())
                    {
                        point current = s.front(); s.pop();
                        labels[current.y][current.x] = label;
                        for (int i = 0; i < 4; ++i) {
                            point next(current.x + permutations[i][0], current.y + permutations[i][1]);
                            if (next.x < 0 || next.y < 0 || next.x >= cols || next.y >= rows) { continue; }
                            if (labels[next.y][next.x] < 0 && map[current.y][current.x] == map[next.y][next.x]) {
                                s.push(next); //Continure BFS here
                            }
                            else if (labels[next.y][next.x] >= 0 && map[current.y][current.x] != map[next.y][next.x]) {
                                //Add neighbour region
                                g[label].insert(labels[next.y][next.x]);
                                g[labels[next.y][next.x]].insert(label);
                            }
                        }
                    }
                    ++label;
                }

            }
        }

        //Shortest path
        int result = dijkstra(labels[rows - 1][cols - 1]);

        //Output
        cout << result << endl;
    }
    return 0;
}
