// https://contest.yandex.ru/contest/59542/problems/F/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const size_t MIN = 0;
const size_t MAX = 1000000001;

int main() {
	size_t w, h, n;
	cin >> w >> h >> n;
	vector<pair<size_t, size_t>> titles(n);
	for (size_t i = 0; i < n; i++) {
		cin >> titles[i].first >> titles[i].second;
	}
	sort(titles.begin(), titles.end());
	vector<size_t>
		prefMin(n, titles[0].second),
		prefMax(n, titles[0].second),
		suffMin(n, titles[n - 1].second),
		suffMax(n, titles[n - 1].second);
	for (size_t i = 1; i < n; i++) {
		prefMin[i] = min(prefMin[i - 1], titles[i].second);
		prefMax[i] = max(prefMax[i - 1], titles[i].second);
	}
	for (size_t i = n - 2; i + 1 > 0; i--) {
		suffMin[i] = min(suffMin[i + 1], titles[i].second);
		suffMax[i] = max(suffMax[i + 1], titles[i].second);
	}	
	size_t l = 0, r = min(w, h), m;
	while (l < r) {
		m = (l + r) / 2;
		bool isFind = false;

		// check
		size_t i = 0, pMax = MIN, pMin = MAX, currMax, currMin;
		for (size_t j = 0; j < n; j++) {
			while (i < n and titles[i].first < titles[j].first + m)
				i++;
			currMax = pMax;
			currMin = pMin;
			if (i != n) {
				currMax = max(currMax, suffMax[i]);
				currMin = min(currMin, suffMin[i]);
			}
			if (currMax - currMin < m) {
				isFind = true;
				break;
			}
			pMax = prefMax[j];
			pMin = prefMin[j];
		}
		if (isFind)
			r = m;
		else
			l = m + 1;
	}
	cout << l;
}
