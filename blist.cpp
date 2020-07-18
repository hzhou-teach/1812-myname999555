/*
 * Jeffrey Chen
 * 10 minutes
 * 10/10 Test Cases
 * Difficulty: 2/10
 * It was a pretty easy bronze problem. I just had to sort the start and end times then traverse through them.
 */
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
	const char* FIN = "blist.in";
	const char* FOUT = "blist.out";
	const char* inFile = argc > 1 ? argv[1] : FIN;
	ifstream cin(inFile);
	ofstream cout(FOUT);
	int n;
	cin >> n;
	vector<int> buckets(n);
	vector<pair<int, int>> times;
	for (int i = 0; i < n; ++i) {
		int s, t, b;
		cin >> s >> t >> b;
		buckets[i] = b;
		times.push_back(make_pair(s, i));
		times.push_back(make_pair(t, i));
	}
	sort(times.begin(), times.end());
	int maxBucket = 0;
	int curBucket = 0;
	vector<bool> inTime(n);
	for (int i = 0; i < 2 * n; ++i) {
		pair<int, int> p = times[i];
		if (!inTime[p.second]) {
			curBucket += buckets[p.second];
			inTime[p.second] = true;
		}
		else {
			curBucket -= buckets[p.second];
			inTime[p.second] = false;
		}
		maxBucket = max(maxBucket, curBucket);
	}
	cout << maxBucket << endl;
	return 0;
}
