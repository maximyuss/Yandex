// https://contest.yandex.ru/contest/66793/problems/J/
#include <iostream>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ifstream cin("input.txt");
	ofstream cout("output.txt");

	int n, m, k;
	cin >> n;
	n++;
	vector<int> arr(n);
	for (int i = 1; i < n; i++)
		cin >> arr[i];
	cin >> m >> k;
	int prev = -1, cnt = k, curr, idx = 1;
	queue<int> q;
	for (int i = 1; i < n; i++) {
		curr = arr[i];
		if (curr < prev) {
			cnt = k;
			idx = i;
			q = queue<int>();
		}
		else if (curr == prev) {
			if (cnt == 0) {
				if (q.empty())
					idx = i;
				else {
					idx = q.front();
					q.pop();
				}
			}
			else
				cnt--;
			if (k != 0)
				q.push(i);
		}
		arr[i] = idx;
		prev = curr;
	}
	vector<int> res(m);
	for (int i = 0; i < m; i++) {
		cin >> curr;
		res[i] = arr[curr];
	}
	for (int e : res)
		cout << e << " ";
	return 0;
}
