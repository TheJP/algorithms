#include <iostream>
#include <set>

using namespace std;

const int Max = 10000;
const int Count = Max + 5;

class Party {
    public:
        set<int> members;
        set<Party*> enemies;
        bool isEnemy(Party * party) {
            return enemies.find(party) != enemies.end();
        };
};

Party* persons[Count];
set<Party*> parties;

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
                    auto tmp = new Party();
                    tmp->members.insert(a); tmp->members.insert(b);
                    parties.insert(tmp);
                    persons[a] = tmp;
                    persons[b] = tmp;
                } else if (persons[a] == nullptr && persons[b] != nullptr) {
                    persons[b]->members.insert(a);
                    persons[a] = persons[b];
                } else if (persons[a] != nullptr && persons[b] == nullptr) {
                    persons[a]->members.insert(b);
                    persons[b] = persons[a];
                } else {
                    if (persons[a]->isEnemy(persons[b])) {
                        cout << "-1" << endl;
                    } else {
                        int sizeA = persons[a]->members.size() + persons[a]->enemies.size();
                        int sizeB = persons[b]->members.size() + persons[b]->enemies.size();
                        auto small = sizeA < sizeB ? persons[a] : persons[b];
                        auto big = sizeA < sizeB ? persons[b] : persons[a];
                        for (auto itr = small->members.begin(); itr != small->members.end(); ++itr) {
                            persons[*itr] = big;
                            big->members.insert(*itr);
                        }
                        for (auto itr = small->enemies.begin(); itr != small->enemies.end(); ++itr) {
                            (*itr)->enemies.insert(big);
                            (*itr)->enemies.erase(small);
                            big->enemies.insert(*itr);
                        }
                        //TODO: merge enemies
                        parties.erase(small);
                        delete small;
                    }
                }
                break;
            //Set enemies
            case 2:
                if (persons[a] == nullptr) {
                    auto tmp = new Party();
                    tmp->members.insert(a);
                    persons[a] = tmp;
                    parties.insert(tmp);
                }
                if (persons[b] == nullptr) {
                    auto tmp = new Party();
                    tmp->members.insert(b);
                    persons[b] = tmp;
                    parties.insert(tmp);
                }
                if (persons[a] == persons[b]) {
                    cout << "-1" << endl;
                } else {
                    persons[a]->enemies.insert(persons[b]);
                    persons[b]->enemies.insert(persons[a]);
                }
                break;
            //Are friends
            case 3:
                if (a != b && (persons[a] == nullptr || persons[b] == nullptr || persons[a] != persons[b])) { cout << '0' << endl; }
                else { cout << '1' << endl; }
                break;
             //Are enemies
            case 4:
                if (a == b || persons[a] == nullptr || persons[b] == nullptr || persons[a] == persons[b] || !persons[a]->isEnemy(persons[b])) { cout << '0' << endl; }
                else { cout << '1' << endl; }
                break;
            default: break;
        }
    } while (cmd != 0);
    for (auto itr = parties.begin(); itr != parties.end(); ++itr) {
        delete *itr;
    }
    return 0;
}