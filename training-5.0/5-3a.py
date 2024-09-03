# https://contest.yandex.ru/contest/59541/problems/A/
n = int(input())
k = int(input())
res = set(input().split())
for i in range(n - 1):
    k = int(input())
    cur = set(input().split())
    res = res & cur
print(len(res))
print(*sorted(res))
