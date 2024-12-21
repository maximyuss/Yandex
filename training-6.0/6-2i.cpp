// https://contest.yandex.ru/contest/66793/problems/I/
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int main() {
	size_t n, tmp;
	cin >> n;
	vector <tuple<int, int, int>> arr[2];
	arr[0].resize(n); arr[1].resize(n);
	vector <int> c(n), d(n);
	for (size_t i = 0; i < n; i++) {
		cin >> tmp;
		arr[0][i] = { tmp, 0, n - i };
		arr[1][i] = { 0, tmp, n - i };
		d[i] = i;
	}
	for (size_t i = 0; i < n; i++) {
		cin >> tmp;
		get<1>(arr[0][i]) = tmp;
		get<0>(arr[1][i]) = tmp;
	}
	for (size_t i = 0; i < n; i++) {
		cin >> c[i];
	}
	sort(arr[0].begin(), arr[0].end());
	sort(arr[1].begin(), arr[1].end());

	int it[2]{ n - 1, n - 1 }, curr, x;
	for (size_t i = 0; i < n; i++) {
		x = c[i];
		while (it[x] > -1 and d[n - get<2>(arr[x][it[x]])] == -1)
			it[x]--;
		curr = n - get<2>(arr[x][it[x]]);
		it[x]--;
		c[i] = curr + 1;
		d[curr] = -1;
	}
	for (int e: c)
		cout << e << " ";
	return 0;
}
