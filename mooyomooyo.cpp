/*
* Jeffrey Chen
* 1 hour 15 min
* 10/10 Test Cases
* 6/10 Difficulty
* This problem was a pretty standard flood-fill. I tried doing a non-recursive flood-fill to challenge myself.
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
using namespace std;

int n, k;
vector<vector<int>> arr;

void gravAll() {
	for (int col = 0; col < 10; ++col) {
		vector<int> newArr;
		for (int i = n - 1; i >= 0; --i) {
			if (arr[i][col] != 0) {
				newArr.push_back(arr[i][col]);
			}
		}
		int cur = newArr.size();
		for (int i = cur; i < n; ++i) {
			newArr.push_back(0);
		}
		for (int i = 0; i < n; ++i) {
			arr[i][col] = newArr[n - i - 1];
		}
	}
}

bool flood(int x, int y) {
	set<pair<int, int>> counted;
	queue<pair<int, int>> waiting;
	vector<vector<int>> tmpArr = arr;
	int colour = tmpArr[x][y];
	int amt = 0;
	waiting.push(make_pair(x, y));
	counted.insert(make_pair(x, y));
	while (!waiting.empty()) {
		pair<int, int> p = waiting.front();
		waiting.pop();
		int nX = p.first;
		int nY = p.second;
		++amt;
		tmpArr[nX][nY] = 0;
		if (1 <= nX && nX < n+1 && 0 <= nY && nY< 10)
			if (tmpArr[nX - 1][nY] == colour && counted.find(make_pair(nX - 1, nY)) == counted.end()) {
					waiting.push(make_pair(nX - 1, nY));
					counted.insert(make_pair(nX - 1, nY));
				}
		if (-1 <= nX && nX < n-1 && 0 <= nY && nY< 10) 
			if (tmpArr[nX + 1][nY] == colour && counted.find(make_pair(nX + 1, nY)) == counted.end()) {
					waiting.push(make_pair(nX + 1, nY));
					counted.insert(make_pair(nX+1, nY));
				}
		if (0 <= nX && nX< n && 1 <= nY && nY< 11) 
			if (tmpArr[nX][nY - 1] == colour && counted.find(make_pair(nX, nY - 1)) == counted.end()) {
					waiting.push(make_pair(nX, nY - 1));
					counted.insert(make_pair(nX, nY-1));
				}
		if (0 <= nX && nX< n && -1 <= (nY) && nY < 9) 
			if (tmpArr[nX][nY + 1] == colour && counted.find(make_pair(nX, nY + 1)) == counted.end()) {
					waiting.push(make_pair(nX, nY + 1));
					counted.insert(make_pair(nX , nY+1));
				}
	}
	if (amt >= k) {
		arr = tmpArr;
		return true;
	}
	return false;
}

bool floodAll() {
	bool check = false;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < n; ++j) {
			if (arr[j][i] != 0) {
				if (flood(j, i)) {
					check = true;
				}
			}
		}
	}
	return check;
}

int main(int argc, char* argv[]) {
	const char* FIN = "mooyomooyo.in";
	const char* FOUT = "mooyomooyo.out";
	const char* inFile = argc > 1 ? argv[1] : FIN;
	ifstream cin(inFile);
	ofstream cout(FOUT); 

	cin >> n >> k;
	for (int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		vector<int> v;
		for (int j = 0; j < 10; ++j) {
			char c = s[j];
			v.push_back(c - '0');
		}
		arr.push_back(v);
	}
	gravAll();
	while (floodAll()) {
		gravAll();
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 10; ++j) {
			cout << arr[i][j];
		}
		cout << endl;
	}
	return 0;
}