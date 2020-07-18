/*
* Jeffrey Chen
* Time: 30 minutes
* 10/10
* Difficulty: 6
* This was a pretty standard binary search. It wasn't too difficult.
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
int n, m, c;
bool work(vector<int> times, int wait) {
	int pointer = 0;
	int bus = 0;
	while (pointer < n && bus < m) {
		int curPos = pointer;
		while (curPos < n && curPos < (pointer + c) && times[curPos] <= (wait+times[pointer])) {
			++curPos;
		}
		pointer = curPos;
		++bus;
	}
	return (pointer == n);
}

int main(int argc, char* argv[]) {
	const char* FIN = "convention.in";
	const char* FOUT = "convention.out";
	const char* inFile = argc > 1 ? argv[1] : FIN;
	ifstream cin(inFile);
	ofstream cout(FOUT);

	//////////////////////////////////////
	// Start your solution from here...

	cin >> n >> m>> c;
	vector<int> times(n);
	for (int i = 0; i < n; ++i) {
		cin >> times[i];
	}
	sort(times.begin(), times.end());

	int low = 0;
	int high = times[n - 1] - times[0];
	while (low < high) {
		int mid = (low + high) / 2;
		if (work(times, mid)) {
			high = mid;
		}
		else {
			low = mid+1;
		}
	}
	cout << low << endl;


	// End of your soulution.
	//////////////////////////////////////

	return 0;
}