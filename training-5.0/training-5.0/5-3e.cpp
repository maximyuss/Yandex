// https://contest.yandex.ru/contest/59541/problems/E/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <deque>

using namespace std;

int main() {
	unordered_map<size_t, size_t> nums;
	vector <unordered_set<size_t>> sNums(3);
	size_t n = 0, num = 0;
	for (size_t i = 0; i < 3; i++) {
		cin >> n;
		for (size_t j = 0; j < n; j++) {
			cin >> num;
			sNums[i].insert(num);
		}
	}
	for (size_t i = 0; i < 3; i++) {
		for (size_t num : sNums[i]) {
			nums[num]++;
		}
	}
	deque<size_t> dq;
	for (auto num : nums) {
		if (num.second > 1)
			dq.push_back(num.first);
	}
	sort(dq.begin(), dq.end());
	for (auto s : dq) {
		cout << s << " ";
	}
	cout << endl;
}
