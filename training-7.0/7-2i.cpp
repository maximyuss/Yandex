// https://contest.yandex.ru/contest/74966/problems/I/
#include <fstream>
#include <vector>
#include <iostream>
#include <climits>
using namespace std;

struct SegmentTree {
    int len;
    vector<int> tree, promises;

    SegmentTree(const vector<int>& nums) {
        int n = nums.size();
        len = 1;
        while (len < n) len <<= 1;

        tree.assign(2 * len, 0);
        promises.assign(2 * len, 0);

        for (int i = 0; i < n; ++i) {
            tree[len + i] = nums[i];
        }

        for (int i = len - 1; i >= 1; --i) {
            tree[i] = max(tree[2 * i], tree[2 * i + 1]);
        }
    }

    void push(int idx) {
        if (promises[idx]) {
            tree[2 * idx] += promises[idx];
            promises[2 * idx] += promises[idx];
            tree[2 * idx + 1] += promises[idx];
            promises[2 * idx + 1] += promises[idx];
            promises[idx] = 0;
        }
    }

    void add(int qLeft, int qRight, int val, int idx = 1, int left = 0, int right = -1) {
        if (right == -1) 
            right = len - 1;
        addInternal(qLeft - 1, qRight - 1, val, idx, left, right);
    }

    void addInternal(int qLeft, int qRight, int val, int idx, int left, int right) {
        if (qLeft > qRight) return;
        if (qLeft == left && qRight == right) {
            tree[idx] += val;
            promises[idx] += val;
        }
        else {
            push(idx);
            int tm = (left + right) / 2;
            addInternal(qLeft, min(qRight, tm), val, 2 * idx, left, tm);
            addInternal(max(qLeft, tm + 1), qRight, val, 2 * idx + 1, tm + 1, right);
            tree[idx] = max(tree[2 * idx], tree[2 * idx + 1]);
        }
    }

    int find(int qLeft, int qRight, int idx = 1, int left = 0, int right = -1) {
        if (right == -1) 
            right = len - 1;
        return findInternal(qLeft - 1, qRight - 1, idx, left, right);
    }

    int findInternal(int l, int qRight, int idx, int left, int right) {
        if (l > qRight) 
            return INT_MIN;
        if (l == left && qRight == right)
            return tree[idx];
        push(idx);
        int tm = (left + right) / 2;
        return max(
            findInternal(l, min(qRight, tm), 2 * idx, left, tm),
            findInternal(max(l, tm + 1), qRight, 2 * idx + 1, tm + 1, right)
        );
    }
};


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n = 0, m = 0;
	cin >> n;
	vector<int> nums(n);
	for (size_t i = 0; i < n; i++)
		cin >> nums[i];
    SegmentTree segTree(nums);
    
    cin >> m;
    string command;
    int arg0, arg1, arg2;
	for (size_t i = 0; i < m; i++) {
		cin >> command >> arg0 >> arg1;
		if (command == "a") {
            cin >> arg2;
            segTree.add(arg0, arg1, arg2);
		}
		else {
            cout << segTree.find(arg0, arg1) << ' ';
		}
	}
	return 0;
}
