// https://contest.yandex.ru/contest/59540/problems/G/

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int main() {
	size_t t, n, tmp, count, _min;
	vector<deque<int>> res;
	cin >> t;
	for (size_t i = 0; i < t; i++) {
		cin >> n;
		count = 0;
		res.push_back({});
		for (size_t j = 0; j < n; j++) {
			cin >> tmp;
			if (count == 0) {
				if (tmp == 1) {
					res[i].push_back(1);
					continue;
				}
				_min = tmp;
			}
			if (tmp == 1) {
				res[i].push_back(count);
				res[i].push_back(1);
				count = 0;
				continue;
			}
			if (tmp <= count) {
				res[i].push_back(count);
				if (tmp == 1) {
					res[i].push_back(1);
					count = 0;
				}
				else {
					_min = tmp;
					count = 1;
				};
				continue;
			}
			count++;
			_min = min(_min, tmp);
			if (tmp == count || count == _min) {
				res[i].push_back(count);
				count = 0;
			}
		}
		if (count > 0)
			res[i].push_back(count);
	}
	for (size_t i = 0; i < t; i++) {
		tmp = res[i].size();
		cout << tmp << endl;
		for (size_t j = 0; j < tmp; j++) {
			if (j > 0) cout << " ";
			cout << res[i][j];
		}
		cout << endl;
	}
}
