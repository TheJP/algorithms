#include <iostream>
#include <set>

using namespace std;

const int Max = 10000;
const int Count = Max + 5;

set<int>* persons[Count];
set<set<int>*> sets;

int main(void) {
    int n, cmd, a, b;
    cin >> n;
    do {
        cin >> cmd >> a >> b;
        switch (cmd)
        {
            //Set friends
            case 1:
                if (persons[a] == nullptr && persons[b] == nullptr) {
                    auto tmp = new set<int>();
                    tmp->insert(a); tmp->insert(b);
                    sets.insert(tmp);
                    persons[a] = tmp;
                    persons[b] = tmp;
                } else if (persons[a] == nullptr && persons[b] != nullptr) {
                    persons[b]->insert(a);
                    persons[a] = persons[b];
                } else if (persons[a] != nullptr && persons[b] == nullptr) {
                    persons[a]->insert(b);
                    persons[b] = persons[a];
                } else {
                    //TODO: Handle impossible friendships!
                    int sizeA = persons[a]->size();
                    int sizeB = persons[b]->size();
                    auto small = sizeA < sizeB ? persons[a] : persons[b];
                    auto big = sizeA < sizeB ? persons[b] : persons[a];
                    for (auto itr = small->begin(); itr != small->end(); ++itr) {
                        persons[*itr] = big;
                        big->insert(*itr);
                    }
                    sets.erase(small);
                    delete small;
                }
                break;
            //Set enemies
            case 2:
                break;
            //Are friends
            case 3:
                if (a != b && (persons[a] == nullptr || persons[b] == nullptr || persons[a] != persons[b])) { cout << '0' << endl; }
                else { cout << '1' << endl; }
                break;
             //Are enemies
            case 4:
                //TODO: Handle special case: different sets, but not enemy (yet)
                if (a == b || persons[a] == nullptr || persons[b] == nullptr || persons[a] == persons[b]) { cout << '0' << endl; }
                else { cout << '1' << endl; }
                break;
            default: break;
        }
    } while (cmd != 0);
    while (!sets.empty())
    {
        auto tmp = sets.back(); sets.pop_back();
        delete tmp;
    }
    return 0;
}