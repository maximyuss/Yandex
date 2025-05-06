# https://contest.yandex.ru/contest/74967/problems/G/
def fenwick_add(i, delta):
    while i <= n:
        fenwick[i] += delta
        i += i & -i

def fenwick_sum(i):
    res = 0
    while i > 0:
        res += fenwick[i]
        i -= i & -i
    return res

import sys
sys.stdin = open('input.txt')
n, k = map(int, input().split())
fenwick = [0] * (n + 1)
nums = [0] * (n + 1)
for I in range(k):
    args = sys.stdin.readline().split()
    if args[0] == 'A':
        i = int(args[1])
        x = int(args[2])
        fenwick_add(i, x - nums[i])
        nums[i] = x
    elif args[0] == 'Q':
        l = int(args[1])
        r = int(args[2])
        print(fenwick_sum(r) - fenwick_sum(l - 1))
