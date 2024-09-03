// https://contest.yandex.ru/contest/59541/problems/A/
#include <iostream>
#include <string>
#include <deque>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
	unordered_map<string, size_t> songs;
	size_t n, k;
	string str;
	cin >> n;
	for (size_t i = 0; i < n; i++) {
		cin >> k;
		for (size_t j = 0; j < k; j++) {
			cin >> str;
			songs[str]++;
		}
	}
	deque<string> dq;
	for (const auto& song : songs) {
		if (song.second == n)
			dq.push_back(song.first);
	}
	sort(dq.begin(), dq.end());
	cout << dq.size() << endl;
	for (auto song : dq) {
		cout << song << " ";
	}
	cout << endl;
}
