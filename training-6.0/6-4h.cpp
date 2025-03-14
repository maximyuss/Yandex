// https://contest.yandex.ru/contest/66795/problems/H/
#include <iostream>
#include <fstream>
#include <vector>
#include <forward_list>
using namespace std;
using my_pair = pair<size_t, size_t>;

vector<forward_list<size_t>> edges;
vector<size_t> prices, dp, res_edges;

my_pair dfs(size_t cur, size_t parent) {
	my_pair sum_prices{ 0, prices[cur] };
	if (next(edges[cur].begin()) == edges[cur].end() and parent > -1)
		return sum_prices;
	for (size_t ele : edges[cur]) {
		if (ele == parent) continue;
		my_pair res = dfs(ele, cur);
		sum_prices.first += res.second;
		sum_prices.second += min(res.first, res.second);
		if (sum_prices.second < sum_prices.first)
			dp[cur] = 1;
	}
	return sum_prices;
}

void dfs_print(size_t cur, size_t parent, size_t& idx, bool must_use) {
	if (must_use or dp[cur] == 1) {
		prices[idx++] = cur;
		must_use = false;
	}
	else
		must_use = true;
	for (size_t ele : edges[cur]) {
		if (ele == parent) continue;
		dfs_print(ele, cur, idx, must_use);
	}
}

int main() {
	ifstream cin("input.txt");
	size_t n, a, b;
	cin >> n;
	edges.resize(n + 1);
	prices.resize(n + 1, 0);
	dp.resize(n + 1, 0);
	for (size_t i = 1; i < n; i++) {
		cin >> a >> b;
		edges[a].push_front(b);
		edges[b].push_front(a);
	}
	for (size_t i = 1; i < n + 1; i++)
		cin >> prices[i];
	if (n == 1)
		cout << prices[1] << ' ' << 1 << '\n' << 1;
	else {
		my_pair res = dfs(1, -1);
		res.first = min(res.first, res.second);
		res.second = 0;
		dfs_print(1, -1, res.second, false);
		cout << res.first << ' ' << res.second << '\n';
		for (size_t i = 0; i < res.second; i++)
			cout << prices[i] << ' ';
	}
	return 0;
}
