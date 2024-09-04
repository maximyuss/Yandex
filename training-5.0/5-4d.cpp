// https://contest.yandex.ru/contest/59542/problems/D/
#include <iostream>
#include <vector>

using namespace std;
const size_t MMAX = 1000000001;

size_t calcLen(const vector<size_t>&arr, size_t width) {
	size_t lines = 1,
		pos = 0;
	for (size_t i = 0; i < arr.size(); i++) {
		if (pos > 0)
			pos++;
		pos += arr[i];
		if (pos > width) {
			lines++;
			pos = arr[i];
			if (pos > width) return MMAX;
		}
	}
	return lines;
}

int main() {
	size_t width, lenA, lenB;
	cin >> width >> lenA >> lenB;
	vector<size_t> arrA (lenA), arrB (lenB);
	for (size_t i = 0; i < lenA; i++)
		cin >> arrA[i];
	for (size_t i = 0; i < lenB; i++)
		cin >> arrB[i];
	size_t l = 1,
		r = width,
		m, linesA, linesB,
		res = MMAX;
	while (l < r) {
		m = (l + r) / 2;
		linesA = calcLen(arrA, m);
		linesB = calcLen(arrB, width - m);
		if (linesA == linesB) {
			res = min(res, linesA);
			break;
		}
		else if (linesA < linesB)
			r = m;
		else
			l = m + 1;
		if (linesA == MMAX) linesA == 0;
		if (linesB == MMAX) linesB == 0;
		res = min(res, max(linesA, linesB));
	}
	cout << res;
}
