// https://contest.yandex.ru/contest/66794/problems/I/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

int main() {
	ifstream cin("input.txt");
	size_t n, a, b;
	cin >> n >> a >> b;
	vector<size_t> order (5);
	bool isDirect;
	if (b < a and not (a == 4 and b == 1) or (a == 1 and b == 4))
		swap(a, b);
	order[a] = 0; 
	order[b] = 1;
	if (b - a == 2) {
		isDirect = true;
		order[a % 4 + 1] = 2;
		order[b % 4 + 1] = 3;
	}
	else {
		isDirect = false;
		order[b % 4 + 1] = 2;
		order[(b % 4 + 1) % 4 + 1] = 3;
	}
	vector<tuple<size_t, size_t, size_t>> rovers(n);
	size_t d, t;
	for (size_t i = 0; i < n; i++) {
		cin >> d >> t;
		rovers[i] = { t, order[d], i };
	}
	for (size_t i = 0; i < 4; i++)
		rovers.push_back({ 1000001, i, 1000 });
	sort(rovers.begin(), rovers.end());
	size_t cnt = 0, cur_time = get<0>(rovers[0]);
	vector<size_t> res(n);
	deque < pair<size_t, size_t>> dq[4];
	for (auto [t, o, i] : rovers) 
		dq[o].push_back({ t,i });
	while (cnt < n) {
		bool isFree = true, canTry = false;
		for (size_t j = 0; j < 4; j++) {
			if (j % 2 == 0)
				canTry = isFree;
			else
				canTry = isDirect or isFree;
			if (!canTry) break;
			auto [t, i] = dq[j].front();
			if (t <= cur_time) {
				res[i] = cur_time;
				dq[j].pop_front();
				cnt++;
				isFree = false;
			}
		}
		cur_time++;
	}
	for (auto e : res)
		cout << e << '\n';
	return 0;
}
