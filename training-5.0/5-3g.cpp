// https://contest.yandex.ru/contest/59541/problems/G/
// Quick but complicated solution
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

struct myPoint {
	int x, y;

	myPoint() : x(0), y(0) {};
	myPoint(const int _x, const int _y) : x(_x), y(_y) {};
	bool operator == (const myPoint& other) {
		return x == other.x && y == other.y;
	};
	bool operator < (const myPoint& other) {
		return x < other.x or (x == other.x && y < other.y);
	};
	myPoint operator + (const myPoint& other) {
		return myPoint{ { x + other.x }, { y + other.y } };
	};
	myPoint operator - (const myPoint& other) {
		return myPoint{ { x - other.x }, { y - other.y } };
	};
	friend std::ostream& operator<< (std::ostream& out, const myPoint& p);
	struct Hash {
		auto operator()(const myPoint& p) const -> size_t {
			return ((size_t)p.x) << 32 | ((size_t)p.y);
		}
	};
	struct Equal {
		auto operator()(const myPoint& p1, const myPoint& p2) const -> bool {
			return p1.x == p2.x && p1.y == p2.y;
		}
	};
};
std::ostream& operator<< (std::ostream& out, const myPoint& p) {
	out << p.x << " " << p.y;
	return out;
}
vector<myPoint> pointLst;
unordered_set<myPoint, myPoint::Hash, myPoint::Equal> pointSet;

vector<myPoint> solve() {
	vector<myPoint> res;
	size_t n = pointLst.size();
	myPoint p1, p2, p3, p4, sum, dif;
	p1 = pointLst[0];
	res = { {p1.x, p1.y + 1}, {p1.x + 1, p1.y}, {p1.x + 1, p1.y + 1} };
	if (n == 1) return res;
	int tmp1, tmp2;
	for (size_t i = 0; i < n; i++) {
		p1 = pointLst[i];
		for (size_t j = i + 1; j < n; j++) {
			p2 = pointLst[j];
			sum = p1 + p2;
			dif = p2 - p1;
			tmp1 = sum.x + dif.y;
			tmp2 = sum.y - dif.x;
			if (abs(tmp1 % 2) == 1 or abs(tmp2 % 2) == 1) continue;
			p3.x = (tmp1) >> 1; p3.y = (tmp2) >> 1;
			p4.x = (sum.x - dif.y) >> 1; p4.y = (sum.y + dif.x) >> 1;
			if (pointSet.contains(p3) and pointSet.contains(p4))
				return {};
			if (res.size() > 1 and pointSet.contains(p3))
				res = { p4 };
			if (res.size() > 1 and pointSet.contains(p4))
				res = { p3 };
			if (res.size() > 2)
				res = { p3, p4 };
		}
	}
	return res;
}

int main() {
	size_t n;
	int x, y;
	cin >> n;
	pointLst.resize(n);
	for (size_t i = 0; i < n; i++) {
		cin >> x >> y;
		pointLst[i] = { x, y };
		pointSet.insert({ x, y });
	}
	vector<myPoint> res = solve();
	cout << res.size() << endl;
	for (auto e : res)
		cout << e << endl;
}
