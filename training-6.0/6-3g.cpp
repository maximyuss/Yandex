// https://contest.yandex.ru/contest/66794/problems/G/
#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ifstream cin("input.txt");
	size_t n, b, a;
	cin >> n >> b;
	unsigned long long res = 0, people = 0;
	for (size_t i = 0; i < n; i++) {
		cin >> a;
		people += a;
		res += people;
		if (b < people)
			people -= b;
		else
			people = 0;
	}
	res += people;
	cout << res;
	return 0;
}
