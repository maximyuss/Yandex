// https://contest.yandex.ru/contest/74966/problems/E/
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

struct Node {
	int key = INT_MAX;
	int val = 0;
	int idx = -1;

	Node() = default;
	Node(int k, int v = 1, int i = -1) : key(k), val(v), idx(i) {}

	static Node merge(const Node& a, const Node& b) {
		if (a.key == b.key)
			return Node(a.key, a.val + b.val);
		return (a.key < b.key) ? a : b;
	}
};

struct SegmentTree {
	int len = 0;
	vector<Node> tree;

	SegmentTree(const vector<int>& nums) {
		int n = nums.size();
		len = 1;
		while (len < n) len <<= 1;
		len--;
		tree.assign(len * 2 + 1, Node());

		for (int i = 0; i < n; ++i) {
			tree[len + i] = Node(nums[i], 1, i + 1);
		}

		for (int i = len - 1; i >= 0; --i) {
			tree[i] = Node::merge(tree[i * 2 + 1], tree[i * 2 + 2]);
		}
	}

	int query(int queryLeft, int queryRight, int k) const {
		auto res = queryInternal(0, 0, len, queryLeft - 1, queryRight - 1, k);
		if (res.second > 0)
			return res.second;
		return -1;
	}

	pair<int, int> queryInternal(int idx, int left, int right, int queryLeft, int queryRight, int k) const {
		if (queryLeft > right || queryRight < left || tree[idx].key>0)
			return { 0, -1 };
		if (queryLeft <= left && right <= queryRight) {
			if (tree[idx].val == 1 && k == 1)
				return { 0, tree[idx].idx };
			if (tree[idx].val < k)
				return { tree[idx].val, -1 };
		}

		int mid = (left + right) / 2;
		auto resLeft = queryInternal(idx * 2 + 1, left, mid, queryLeft, queryRight, k);
		if (resLeft.second > 0)
			return resLeft;
		auto resRight = queryInternal(idx * 2 + 2, mid + 1, right, queryLeft, queryRight, k - resLeft.first);
		if (resRight.second > 0)
			return resRight;
		return { resLeft.first + resRight.first, -1 };
	}

	void update(int idx, int key) {
		idx += len;
		tree[idx].key = key;
		while (idx > 0) {
			idx = (idx - 1) >> 1;
			tree[idx] = Node::merge(tree[idx * 2 + 1], tree[idx * 2 + 2]);
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n = 0, k = 0;
	cin >> n;
	vector<int> nums(n);
	for (size_t i = 0; i < n; i++)
		cin >> nums[i];
	SegmentTree segTree(nums);
	cin >> k;
	for (size_t i = 0; i < k; i++) {
		string command;
		int arg0 = 0, arg1 = 0, arg2 = 0;
		cin >> command >> arg0 >> arg1;
		if (command == "s") {
			cin >> arg2;
			cout << segTree.query(arg0, arg1, arg2) << " ";
		}
		else
			segTree.update(arg0 - 1, arg1);
	}
	return 0;
}
