#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <tuple>

using namespace std;

const int Colors = 51; //Exclusive upper bound (Colors from 1 to 50)
const char* ErrorMessage = "some beads may be lost";
typedef vector<set<size_t>> Graph;

vector<bool> visited(Colors);
vector<bool> processed(Colors);
vector<size_t> parent(Colors);

void findPath(size_t start, size_t end, vector<size_t> & vec) {
    if (start == end) { vec.push_back(start); }
    else {
        findPath(start, parent[end], vec);
        vec.push_back(end);
    }
}

//Custom dfs, which returns first found cycle
vector<size_t>* nextCycle(size_t current, Graph & g) {
    visited[current] = true;
    for (auto itr = g[current].begin(); itr != g[current].end(); ++itr) {
        if (!visited[*itr]) {
            parent[*itr] = current;
            auto cycle = nextCycle(*itr, g);
            if (cycle != nullptr) { return cycle; }
        } else {
            if (!processed[*itr]) {
                if (parent[current] != *itr) {
                    auto cycle = new vector<size_t>();
                    findPath(*itr, current, *cycle);
                    return cycle;
                }
            }
        }
    }
    processed[current] = true;
    return nullptr;
}

bool combine(vector<size_t>* necklace, vector<size_t>* cycle) {
    for (auto itr = necklace->begin(); itr != necklace->end(); ++itr) {
        for (auto itr2 = cycle->begin(); itr2 != cycle->end(); ++itr2) {
            if (*itr == *itr2) {
                auto diff = itr - necklace->begin();
                necklace->insert(itr, cycle->begin(), itr2);
                necklace->insert(necklace->begin() + diff, itr2, cycle->end());
                return true;
            }
        }
    }
    return false;
}

void removeEdge(size_t a, size_t b, Graph & g) {
    for (auto itr2 = g[a].begin(); itr2 != g[a].end(); ++itr2) {
        if (*itr2 == b) { g[a].erase(itr2); break; }
    }
    for (auto itr2 = g[b].begin(); itr2 != g[b].end(); ++itr2) {
        if (*itr2 == a) { g[b].erase(itr2); break; }
    }
}

void solve(int t) {
    size_t n; //5 <= n <= 1000, Beads
    cin >> n;
    Graph g(Colors);
    set<size_t> used;
    vector<tuple<size_t, size_t, int>> dupes;
    size_t a, b;
    for (size_t i = 0; i < n; ++i) {
        cin >> a >> b;
        if (g[a].find(b) != g[a].end()) {
            bool found = false;
            size_t x, y, z;
            for (auto itr = dupes.begin(); itr != dupes.end(); ++itr) {
                tie(x, y, z) = *itr;
                if (min(a, b) == x && max(a, b) == y) {
                    found = true;
                    dupes.erase(itr);
                    break;
                }
            }
            if (!found) { z = 0; }
            dupes.push_back(make_tuple(min(a, b), max(a, b), z + 1));
            //dupes a,b already exists in g[a], g[b] and used
        } else if (a == b) {
            dupes.push_back(make_tuple(a, b, 1));
            used.insert(a);
        } else {
            g[a].insert(b);
            g[b].insert(a);
            used.insert(a);
            used.insert(b);
        }
    }
    cout << "Case #" << t << endl;
    //Check even deg
    size_t counts[Colors];
    for (int i = 1; i < Colors; ++i) { counts[i] = g[i].size(); }
    for (auto itr = dupes.begin(); itr != dupes.end(); ++itr) {
        counts[get<0>(*itr)] += get<2>(*itr);
        counts[get<1>(*itr)] += get<2>(*itr);
    }
    for (int i = 1; i < Colors; ++i) {
        if ((counts[i] & 1) == 1) {
            //No eulerian cycle possible
            cout << ErrorMessage << endl;
            return;
        }
    }
    //Check connected
    fill(visited.begin(), visited.end(), false);
    queue<size_t> bfs;
    bfs.push(*used.begin()); //Use any used color
    visited[bfs.front()] = true;
    while (!bfs.empty())
    {
        size_t current = bfs.front(); bfs.pop();
        for (auto itr = g[current].begin(); itr != g[current].end(); ++itr) {
            if (!visited[*itr]) {
                visited[*itr] = true;
                bfs.push(*itr);
            }
        }
    }
    for (auto itr = used.begin(); itr != used.end(); ++itr) {
        if (!visited[*itr]) {
            cout << ErrorMessage << endl;
            return;
        }
    }
    //Remove the dupes from the graph
    vector<vector<size_t>*> cycles;
    for (auto itr = dupes.begin(); itr != dupes.end(); ++itr) {
        size_t x, y, z;
        tie(x, y, z) = *itr;
        if (z % 2 != 0) {
            ++z;
            if (x != y) {
                g[x].erase(y);
                g[y].erase(x);
            }
        }
        z /= 2;
        auto cycle = new vector<size_t>();
        for (size_t i = 0; i < z; ++i) {
            cycle->push_back(x);
            if (x != y) { cycle->push_back(y); }
        }
        cycles.push_back(cycle);
    }
    //Eulerian path possible: find and print it
    int edges = n;
    vector<size_t>* necklace = nullptr;
    if (!cycles.empty()) {
        necklace = cycles.back();
        cycles.pop_back();
        edges -= necklace->size();
    }
    while (edges > 0)
    {
        //Reset visited
        vector<size_t>* cycle = nullptr;
        auto usedItr = used.begin();
        while (cycle == nullptr && usedItr != used.end())
        {
            fill(visited.begin(), visited.end(), false);
            fill(processed.begin(), processed.end(), false);
            fill(parent.begin(), parent.end(), -1);
            cycle = nextCycle(*usedItr, g);
            ++usedItr;
        }
        if (cycle != nullptr) {
            //Remove those edges from the graph, which are contained in the cycle
            for (auto itr = cycle->begin(); itr + 1 != cycle->end(); ++itr) {
                removeEdge(*itr, *(itr + 1), g);
            }
            removeEdge(*cycle->begin(), *(cycle->end() - 1), g);
            //Place found cycle in the existing necklace
            if (necklace == nullptr) { necklace = cycle; edges -= cycle->size(); }
            else { cycles.push_back(cycle); }
        }
        auto itr = cycles.begin();
        while (itr != cycles.end()) {
            if (combine(necklace, *itr)) {
                edges -= (*itr)->size();
                delete *itr;
                cycles.erase(itr);
                itr = cycles.begin();
            }
            else { ++itr; }
        }
    }
    //Print result
    for (auto itr = necklace->begin(); itr + 1 != necklace->end(); ++itr) {
        cout << *itr << ' ' << *(itr + 1) << endl;
    }
    cout << *(necklace->end() - 1) << ' ' << *necklace->begin() << endl;
    delete necklace;
}

int main(void) {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        if (i != 0) { cout << endl; }
        solve(i + 1);
    }
    return 0;
}
