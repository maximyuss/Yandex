// https://contest.yandex.ru/contest/74966/problems/J/
#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;
const int P = 10000019;
const int INV_P_MINUS_ONE = 514221978;

vector<int> powP;

struct SegmentTree {
    int len;
    vector<int> tree, promises;
    vector<int> size;

    SegmentTree(const vector<int>& nums) {
        int n = nums.size();
        len = 1;
        while (len < n) len <<= 1;
        tree.resize(len * 2);
        promises.assign(len * 2, -1);
        size.assign(len * 2, 1);

        for (int i = len; i < len + n; ++i)
            tree[i] = nums[i - len];

        for (int i = len - 1; i > 0; --i) {
            size[i] = size[i << 1] + size[i << 1 | 1];
            tree[i] = (1LL * tree[i << 1] * powP[size[i << 1 | 1]] + tree[i << 1 | 1]) % MOD;
        }
    }

    void apply(int idx, int val) {
        tree[idx] = 1LL * val * (powP[size[idx]] - 1 + MOD) % MOD * INV_P_MINUS_ONE % MOD;
        if (idx < len) 
            promises[idx] = val;
    }

    void push(int idx) {
        if (promises[idx] != -1) {
            apply(idx << 1, promises[idx]);
            apply(idx << 1 | 1, promises[idx]);
            promises[idx] = -1;
        }
    }

    void change(int qLeft, int qRight, int val, int idx = 1, int left = 0, int right = -1) {
        if (right == -1) 
            right = len - 1;
        if (qLeft > qRight) 
            return;
        if (qLeft == left && qRight == right) {
            apply(idx, val);
        }
        else {
            push(idx);
            int tm = (left + right) / 2;
            change(qLeft, min(qRight, tm), val, idx << 1, left, tm);
            change(max(qLeft, tm + 1), qRight, val, idx << 1 | 1, tm + 1, right);
            tree[idx] = (1LL * tree[idx << 1] * powP[size[idx << 1 | 1]] + tree[idx << 1 | 1]) % MOD;
        }
    }

    int getHash(int qLeft, int qRight, int idx = 1, int left = 0, int right = -1) {
        if (right == -1) 
            right = len - 1;
        if (qLeft > qRight) 
            return 0;
        if (qLeft == left && qRight == right)
            return tree[idx];
        push(idx);
        int tm = (left + right) / 2;
        int resLeft = getHash(qLeft, min(qRight, tm), idx << 1, left, tm);
        int resRight = getHash(max(qLeft, tm + 1), qRight, idx << 1 | 1, tm + 1, right);
        int lenRight = max(0, qRight - max(qLeft, tm + 1) + 1);
        return (1LL * resLeft * powP[lenRight] + resRight) % MOD;
    }

    bool compare(int left1, int left2, int k) {
        return getHash(left1, left1 + k - 1) == getHash(left2, left2 + k - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n;
    powP.resize(n);
    powP[0] = 1;
    for (size_t i = 1; i < n; ++i)
        powP[i] = 1LL * powP[i - 1] * P % MOD;
    vector<int> nums(n);
    for (int& x : nums) 
        cin >> x;
    SegmentTree segTree(nums);
    cin >> m;
    int command, arg0, arg1, arg2;
    while (m--) {
        int type;
        cin >> command >> arg0 >> arg1 >> arg2;
        if (command == 0) {
            segTree.change(arg0 - 1, arg1 - 1, arg2);
        }
        else {
            cout << (segTree.compare(arg0 - 1, arg1 - 1, arg2) ? "+" : "-");
        }
    }
    return 0;
}
