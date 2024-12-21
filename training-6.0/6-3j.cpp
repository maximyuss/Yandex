// https://contest.yandex.ru/contest/66794/problems/J/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

int main() {
	const size_t maxValue = 1000000001;
	ifstream cin("input.txt");
	size_t n, height;
	cin >> n >> height;
	vector<pair<size_t, size_t>> arr(n);
	for (size_t i = 0; i < n; i++)
		cin >> arr[i].first; // H
	for (size_t i = 0; i < n; i++)
		cin >> arr[i].second; // W
	arr.push_back({ 10 * maxValue, 0 });
	sort(arr.begin(), arr.end());
	deque<pair<size_t, size_t>> dq; // index, discomfort
	dq.push_back({ 0,0 });
	size_t l = 0, r = 1, lastHeight = arr[0].first;
	unsigned long long sumWidth = arr[0].second,discomfort = 0, res = maxValue;
	while (l < n) {
		while (r <= n and sumWidth < height) {
			discomfort = arr[r].first - lastHeight;
			while (!dq.empty() and dq.back().second <= discomfort)
				dq.pop_back();
			sumWidth += arr[r].second;
			dq.push_back({ r, discomfort });
			lastHeight = arr[r].first;
			r++;
		}
		auto head = dq.front();
		discomfort = head.second;
		if (discomfort < res) {
			res = discomfort;
			if (res == 0) break;
		}
		sumWidth -= arr[l].second;
		l++;
		if (l >= head.first)
			dq.pop_front();

	}
	cout << res << '\n';
	return 0;
}
