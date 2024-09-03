# https://contest.yandex.ru/contest/59541/problems/C/
n = int(input())
cnt = {}
for e in map(int, input().split()):
    cnt[e] = cnt.get(e, 0) + 1
count = 0
for e in cnt:
    count = max(count, cnt[e] + cnt.get(e + 1, 0))
print(n - count)
