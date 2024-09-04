// https://contest.yandex.ru/contest/59541/problems/H/
#include <cstdint>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

struct pair_hash {
	uint32_t operator()(const pair<int, int>& p) const {
		uint16_t a16 = p.first,
			b16 = p.second;
		return ((uint32_t)a16 << 16) | b16;
	}
};

int main() {
	size_t n;
	int x1, x2, y1, y2, dx, dy, shiftX, shiftY;
	unordered_map <pair<int, int>, set<pair<int, int>>, pair_hash> map1;
	unordered_map <pair<int, int>, size_t, pair_hash> map2;
	cin >> n;
	for (size_t i = 0; i < 2; i++)
		for (size_t j = 0; j < n; j++) {
			cin >> x1 >> y1 >> x2 >> y2;
			if (x1 > x2 || x1 == x2 && y1 > y2) {
				swap(x1, x2); swap(y1, y2);
			}
			dx = x2 - x1; dy = y2 - y1;
			if (i == 0)
				map1[{dx, dy}].insert({ x1, y1 });
			else
				for (const auto& [x, y] : map1[{dx, dy}]) {
					shiftX = x1 - x;
					shiftY = y1 - y;
					map2[{shiftX, shiftY}]++;
				}
		}
	size_t max_shift = 0;
	for (const auto& shift : map2) {
		max_shift = max(max_shift, shift.second);
	}
	cout << n - max_shift;
}
