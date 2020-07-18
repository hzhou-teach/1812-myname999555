/*
* Jeffrey Chen
* Time: 30 minutes
* 10/10 Test Cases
* Difficulty: 4/10
* I just used a priority queue for the seniority, and the problem wasn't too hard to finish from there.
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
#include <unordered_map>
#include <unordered_set>

using namespace std;

bool sortFirst(vector<int> v1, vector<int> v2) {
	return v1[0] < v2[0];
}

struct compSenior {
	bool operator()(vector<int> const& v1, vector<int> const& v2) {
		return v1[2] > v2[2];
	}
};

int n;
int main(int argc, char* argv[]) {
	const char* FIN = "convention2.in";
	const char* FOUT = "convention2.out";
	const char* inFile = argc > 1 ? argv[1] : FIN;
	ifstream cin(inFile);
	ofstream cout(FOUT);

	//////////////////////////////////////
	// Start your solution from here...

	cin >> n;
	vector<vector<int>> cows;
	for (int i = 0; i < n; ++i) {
		int a, t;
		cin >> a >> t;
		vector<int> v;
		v.push_back(a);
		v.push_back(t);
		v.push_back(i);
		cows.push_back(v);
	}

	sort(cows.begin(), cows.end(), sortFirst);
	int maxTime = 0;
	priority_queue <vector<int>, vector<vector<int>>, compSenior> waiting;
	int curBegin = cows[0][0];
	int curEnd = cows[0][0];
	int curCow = 0;
	for (int i = 0; i < n; ++i) {
		if (!waiting.empty()) {
			vector<int> curStat = waiting.top();
			waiting.pop();
			maxTime = max(maxTime, curEnd - curStat[0]);
			curBegin = curEnd;
			curEnd += curStat[1];
		}
		else {
			curBegin = cows[curCow][0];
			curEnd = cows[curCow][0];
			while (curCow < n && cows[curCow][0] == curBegin) {
				waiting.push(cows[curCow]);
				++curCow;
			}
			vector<int> curStat = waiting.top();
			waiting.pop();
			maxTime = max(maxTime, curEnd - curStat[0]);
			curBegin = curEnd;
			curEnd += curStat[1];
		}
		while (curCow < n && cows[curCow][0] <= curEnd) {
			waiting.push(cows[curCow]);
			++curCow;
		}
	}

	cout << maxTime << endl;

	// End of your soulution.
	//////////////////////////////////////

	return 0;
}