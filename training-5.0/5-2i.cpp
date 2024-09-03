// https://contest.yandex.ru/contest/59540/problems/I/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n, row, col;
	cin >> n;
	vector<pair<int, int>> ships(n);
	for (size_t i = 0; i < n; i++) {
		cin >> row >> col;
		ships[i] = { row, col };
	}
	sort(ships.begin(), ships.end());
	int res = n * n, count;
	for (int i = 1; i <= n; i++) {
		count = 0;
		for (int j = 0; j < n; j++)
			count += abs(ships[j].first - j - 1) + abs(ships[j].second - i);
		res = min(res, count);
	}
	cout << res;
}
