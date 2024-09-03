// https://contest.yandex.ru/contest/59541/problems/B/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	size_t w1[26]{}, w2[26]{};
	string s1, s2;
	bool res = true;
	getline(cin, s1);
	getline(cin, s2);
	for (size_t i = 0; i < size(s1); i++) {
		w1[s1[i] - 'a']++;
		w2[s2[i] - 'a']++;
	}
	for (size_t i = 0; i < 26; i++)
		if (w1[i] != w2[i]) {
			res = false;
			break;
		}
	if (res)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
}
