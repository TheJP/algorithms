#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;

map<string, int> cnames;
vector<pair<int, int> > graph[10005]; //cost, city
vector<priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > > djqueue; //cost, city
vector<int> djdist[10005];

int main(void){
	int n, ncities, ncitiesbefore = 0, nrows, i, j, k, city, city2;
	char input[10];
	pair<int, int> stdpair, stdpair2;
	scanf("%d", &n);
	for (i = 0; i<n; i++){
		scanf("%d", &ncities);
		//init
		for (j = min(ncities, ncitiesbefore); j >= 0; j--){
			graph[j].clear();
			djdist[j].clear();
		}
		djqueue.clear();
		cnames.clear();
		//read
		for (j = 1; j <= ncities; j++){
			scanf("%s", &input);
			cnames[string(input)] = j;
			scanf("%d", &nrows);
			for (k = 0; k<nrows; k++){
				scanf("%d %d", &stdpair.second, &stdpair.first);
				graph[j].push_back(stdpair);
			}
		}
		//dj
		scanf("%d", &nrows);
		djqueue.resize(ncities + 1);
		for (j = 0; j<nrows; j++){
			scanf("%s", &input);
			city = cnames[input];
			scanf("%s", &input);
			city2 = cnames[input];
			if ((djdist[city].empty() || djdist[city][city2] == 2147483647)  /* Nicht explicit 'undirected'*/ && (djdist[city2].empty() || djdist[city2][city] == 2147483647)){
				if (djdist[city].empty()){
					djdist[city].resize(ncities + 1, 2147483647);
					stdpair.first = 0;
					stdpair.second = city;
					djqueue[city].push(stdpair);
					djdist[city][city] = 0;
				}
				while (!djqueue[city].empty()){
					stdpair = djqueue[city].top();
					djqueue[city].pop();
					if (stdpair.second == city2) { djdist[city][stdpair.second] = stdpair.first; break; }
					if (djdist[city][stdpair.second] == stdpair.first){
						for (k = graph[stdpair.second].size() - 1; k >= 0; k--){
							stdpair2 = graph[stdpair.second][k];
							stdpair2.first += stdpair.first;
							if (djdist[city][stdpair2.second] > stdpair2.first){
								djdist[city][stdpair2.second] = stdpair2.first;
								djqueue[city].push(stdpair2);
							}
						}
					}
				}
			}
			//ausgabe
			if (!djdist[city].empty() && djdist[city][city2] != 2147483647){
				printf("%d\n", djdist[city][city2]);
			}/* Nicht explicit 'undirected'*/ else{
				printf("%d\n", djdist[city2][city]);
			}
		}

		ncitiesbefore = ncities;
	}
	return 0;
}