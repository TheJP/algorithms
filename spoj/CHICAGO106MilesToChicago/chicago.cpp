#include <iostream>
#include <cstdio>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

vector<vector<pair<double, int> > > graph;
priority_queue<pair<double, int> > djque;
double djdist[105];

int main(void){
	int nv, ne;//n,m
	int i, j, a, b, w;
	pair<double, int> stdpair, stdpair2;
	scanf("%d", &nv);
	do{
		scanf("%d", &ne);
		//clear
		graph.clear();
		graph.resize(nv + 3);
		for (i = 0; i <= nv; i++){
			djdist[i] = 0.0;
		}
		//input
		for (i = 0; i<ne; i++){
			scanf("%d%d%d", &a, &b, &w);
			stdpair.first = w / 100.0;
			stdpair.second = b;
			graph[a].push_back(stdpair);
			stdpair.second = a;
			graph[b].push_back(stdpair);
		}
		//dj
		stdpair.first = 1;
		stdpair.second = 1;
		djque.push(stdpair);
		while (!djque.empty()){
			stdpair = djque.top();
			djque.pop();
			if (stdpair.second == nv){ printf("%f percent\n", stdpair.first * 100); while (!djque.empty()){ djque.pop(); } break; }
			for (i = graph[stdpair.second].size() - 1; i >= 0; i--){
				stdpair2 = graph[stdpair.second][i];
				stdpair2.first *= stdpair.first;
				if (djdist[stdpair2.second] < stdpair2.first){
					djdist[stdpair2.second] = stdpair2.first;
					djque.push(stdpair2);
				}
			}
		}
		scanf("%d", &nv);
	} while (nv != 0);
	return 0;
}