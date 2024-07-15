// https://contest.yandex.ru/contest/59540/problems/H/

#include <iostream>
#include <vector>
using namespace std;
struct typeMax { int value, i, j; };

typeMax findMax(const auto& data, int exeptI = -1, int exeptJ = -1) {
	typeMax res = { -1,0,0 };
	for (int i = 0; i < data.size(); i++) {
		if (i == exeptI) continue;
		for (int j = 0; j < data[0].size(); j++)
			if (j != exeptJ && data[i][j] > res.value)
				res = { data[i][j], i, j };
	}
	return res;
}

int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> data(n, vector<int>(m, 0));
	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < m; j++)
			cin >> data[i][j];
	typeMax mainMax = findMax(data);
	typeMax firstOnCol = findMax(data, mainMax.i, -1);
	typeMax firstOnRow = findMax(data, mainMax.i, firstOnCol.j);
	typeMax secondOnRow = findMax(data, -1, mainMax.j);
	typeMax secondOnCol = findMax(data, secondOnRow.i, mainMax.j);
	if (firstOnRow.value < secondOnCol.value)
		printf("%d %d\n", mainMax.i + 1, firstOnCol.j + 1);
	else
		printf("%d %d\n", secondOnRow.i + 1, mainMax.j + 1);
}
