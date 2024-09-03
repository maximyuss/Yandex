// https://contest.yandex.ru/contest/59540/problems/J
//Quick but complicated solution
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct MyPoint {
	size_t i;
	size_t j;
};
struct MyArea {
	size_t size;
	MyPoint cLT;	//left top corner
	MyPoint cRB;	//right bottom corner
};

size_t n, m;
vector<string> arr;
vector<MyArea> areas;
int currArea = -1;
char sym[2]{ 'a', 'b' };

void fillArea(int type, size_t row, size_t col) {
	size_t bottom = m,
		right = n;
	if (type == 0) {
		// horizontal check
		for (size_t i = row; i <= bottom; i++) {
			if (arr[i + 1][col] != '#' || arr[i + 1][col - 1] == '#')
				bottom = i;
			for (size_t j = col; j <= right; j++) {
				if (arr[i][j + 1] != '#') {
					right = j;
					break;
				}
			}
		}
	}
	else {
		// vertical check
		for (size_t j = col; j <= right; j++) {
			if (arr[row][j + 1] != '#' || arr[row + 1][j - 1] == '#')
				right = j;
			for (size_t i = row; i <= bottom; i++) {
				if (arr[i + 1][j] != '#') {
					bottom = i;
					break;
				}
			}
		}
	}
	auto& _ = areas[currArea];
	for (size_t i = row; i <= bottom; i++) {
		for (size_t j = col; j <= right; j++) {
			_.size++;
			arr[i][j] = sym[currArea];
		}
	}
	_.cLT = { row, col };
	_.cRB = { bottom, right };
}

void reFillRectangleArea() {
	auto& _ = areas[0];
	size_t width = _.cRB.j - _.cLT.j + 1,
		height = _.cRB.i - _.cLT.i + 1;
	if (width >= height) {
		for (size_t i = _.cLT.i; i <= _.cRB.i; i++)
			arr[i][areas[0].cRB.j] = sym[1];
	}
	else
		for (size_t j = _.cLT.j; j <= _.cRB.j; j++)
			arr[areas[0].cRB.i][j] = sym[1];
}

bool checkPicture(int type) {
	for (size_t i = 1; i <= m; i++) {
		for (size_t j = 1; j <= n; j++) {
			if (arr[i][j] == '#') {
				if (currArea == 1) return false; // Too much areas

				areas.push_back({});
				currArea++;
				auto& _ = areas[currArea];
				_.size = 0;
				_.cLT = { m, n };
				_.cRB = { 0, 0 };
				fillArea(type, i, j);
			}
		}
	}
	if (currArea == -1) return false;
	if (currArea == 0) {
		if (areas[currArea].size == 1) return false;
		reFillRectangleArea();
	}
	return true;
}

void clearAll() {
	areas.clear();
	currArea = -1;
	for (size_t i = 1; i <= m; i++)
		for (size_t j = 1; j <= n; j++)
			if (arr[i][j] != '.') arr[i][j] = '#';
}

void input() {
	cin >> m >> n;
	arr.resize(m + 2);
	string tmp(n + 2, '.');
	arr[0] = tmp;
	arr[m + 1] = tmp;
	for (size_t i = 1; i <= m; i++) {
		cin >> tmp;
		arr[i] = '.' + tmp + '.';
	}
}

void task_5_2_J() {
	input();
	if (!checkPicture(0)) {
		clearAll();
		if (!checkPicture(1)) {
			cout << "NO" << endl;
			return;
		}
	}
	cout << "YES" << endl;
	for (size_t i = 1; i <= m; i++) {
		cout << arr[i].substr(1, n) << endl;
	}
}

int main() {
	task_5_2_J();
	return 0;
}
