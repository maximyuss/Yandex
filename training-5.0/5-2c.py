# https://contest.yandex.ru/contest/59540/problems/C/

n = int(input())
a = list(map(int, input().split()))
max_a = max(a)
sum_a = sum(a)
res = 2 * max_a - sum_a if 2 * max_a > sum_a else sum_a
print(res)
