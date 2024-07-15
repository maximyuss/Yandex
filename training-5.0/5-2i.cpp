// https://contest.yandex.ru/contest/59540/problems/I/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct point { int row;	int col; };
vector<point> ships;

int solveForCol(int col) {
	int res = 0,
		n = ships.size();
	vector<int> calc(n, 0);
	col++;
	for (size_t i = 0; i < n; i++) {
		res += abs(ships[i].col - col);
		++calc[ships[i].row - 1];
	}
	int i = 0,
		j = 0,
		delta = -1;
	while (i < n && j < n) {
		while (i < n && calc[i] > 0) i++;
		while (j < n && calc[j] < 2) j++;
		if (i == n) break;
		calc[i] = 1;
		calc[j]--;
		res += abs(i - j);
	}
	return res;
}

int task_5_2_I() {
	int minCol = 0,
		curCol = 0;
	for (size_t i = 0; i < ships.size(); i++) {
		curCol = solveForCol(i);
		if (i == 0)
			minCol = curCol;
		else
			minCol = min(minCol, curCol);
	}
	return minCol;
}

void input() {
	int n, row, col;
	cin >> n;
	for (size_t i = 0; i < n; i++) {
		cin >> row >> col;
		ships.push_back({ row, col });
	}
}

int main() {
	input();
	cout << task_5_2_I();
}
