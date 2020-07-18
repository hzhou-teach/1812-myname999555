/*
* Jeffrey Chen
* 2 hours
* 3/10 Test Cases
* 10/10 Difficulty
* I tried implementing dijkstra to check the distance between any pair of barns, but it was too slow so I only got 3/10 test cases.
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <climits>
#include <unordered_map>
#include <unordered_set>

using namespace std;
int n, m, k;
int INFTY = INT_MAX;


vector<int> dijkstra(vector<vector<pair<int, int>>> graph, int source) {
	set<int> q;
	vector<int> dist(n);
	vector<bool> visit(n);
	int curNode = source;
	for (int i = 0; i < n; ++i) {
		dist[i] = INFTY;
		q.insert(i);
	}
	dist[source] = 0;
	while (!q.empty()) {
		int minAmt = INFTY;
		int minPoint = -1;
		for (int i = 0; i < graph[curNode].size(); ++i) {
			int onNode = graph[curNode][i].first;
			if (visit[onNode]) {
				continue;
			}
			int newAmt = dist[curNode] + graph[curNode][i].second;
			if (newAmt < dist[onNode]) {
				dist[onNode] = newAmt;
			}
		}
		set<int>::iterator itr;
		for (itr = q.begin(); itr != q.end(); ++itr) {
			if (dist[*itr] < minAmt) {
				minAmt = dist[*itr];
				minPoint = *itr;
			}
		}
		q.erase(curNode);
		visit[curNode] = true;
		curNode = minPoint;
	}
	return dist;
}

int main(int argc, char* argv[]) {
	const char* FIN = "dining.in";
	const char* FOUT = "dining.out";
	const char* inFile = argc > 1 ? argv[1] : FIN;
	ifstream cin(inFile);
	ofstream cout(FOUT);

	cin >> n >> m >> k;
	vector<vector<pair<int, int>>> graph(n);
	for (int i = 0; i < m; ++i) {
		int a, b, t;
		cin >> a >> b >> t;
		graph[a - 1].push_back(make_pair(b - 1, t));
		graph[b - 1].push_back(make_pair(a - 1, t));
	}
	vector<int> hay(n);
	vector<int> posHay;
	for (int i = 0; i < k; ++i) {
		int ind, y;
		cin >> ind >> y;
		if (hay[ind - 1] == 0) {
			posHay.push_back((ind - 1));
		}
		if (y > hay[ind - 1]) {
			hay[ind - 1] = y;
		}
	}

	vector<vector<int>> distBtw;
	for (int i = 0; i < n; ++i) {
		distBtw.push_back(dijkstra(graph, i));
	}
	vector<bool> possible(n-1);
	for (int i = 0; i < n - 1; ++i) {
		bool work = false;
		for (int j = 0; j < posHay.size(); ++j) {
			int hayNode = posHay[j];
			int time = (distBtw[i][hayNode] + distBtw[hayNode][n - 1]);
			if ((time-distBtw[i][n-1]) <= hay[hayNode]) {
				work = true;
			}
		}
		possible[i] = work;
	}
	for (int i = 0; i < n - 1; ++i) {
		if (possible[i]) {
			cout << 1;
		}
		else {
			cout << 0;
		}
		cout << endl;
	}

	return 0;
}
