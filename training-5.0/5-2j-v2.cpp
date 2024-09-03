// https://contest.yandex.ru/contest/59540/problems/J
//Slow, but simple solution
#include <iostream>
#include <string>
#include <vector>

using namespace std;
struct MyPoint { size_t r; size_t c; };

bool isRect(auto& arr, size_t r0, size_t c0, size_t r1, size_t c1, char fill) {
	size_t count = 0;
	MyPoint cLT{ r1, c1 }, cRB{ 0, 0 };
	for (size_t row = r0; row <= r1; row++) {
		for (size_t col = c0; col <= c1; col++) {
			if (arr[row][col] != '.') {
				cLT = { min(cLT.r, row), min(cLT.c, col) };
				cRB = { max(cRB.r, row), max(cRB.c, col) };
				count++;
				arr[row][col] = fill;
			}
		}
	}
	return (count > 0 and (cRB.c - cLT.c + 1) * (cRB.r - cLT.r + 1) == count);
}

void printArr(const auto& arr) {
	cout << "YES" << endl;
	for (auto line : arr)
		cout << line << endl;
}

int main() {
	size_t n, m;
	cin >> m >> n;
	vector<string> arr(m);
	MyPoint 
		cLT{ m, n }, //left top corner
		cRB{ 0, 0 }; // right bottom corner
	for (size_t row = 0; row < m; row++) {
		cin >> arr[row];
		for (size_t col = 0; col < n; col++) {
			if (arr[row][col] != '.') {
				cLT = { min(cLT.r, row), min(cLT.c, col) };
				cRB = { max(cRB.r, row), max(cRB.c, col) };
			}
		}
	}
	for (size_t row = cLT.r; row < cRB.r; row++) {
		if (isRect(arr, cLT.r, cLT.c, row, cRB.c, 'a') and
			isRect(arr, row + 1, cLT.c, cRB.r, cRB.c, 'b')) {
			printArr(arr);
			return 0;
		}
	}
	for (size_t col = cLT.c; col < cRB.c; col++) {
		if (isRect(arr, cLT.r, cLT.c, cRB.r, col, 'a') and 
			isRect(arr, cLT.r, col + 1, cRB.r, cRB.c, 'b')) {
			printArr(arr);
			return 0;
		}
	}
	cout << "NO" << endl;
	return 0;
}
