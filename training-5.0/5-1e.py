# https://contest.yandex.ru/contest/59539/problems/E
# 5-1E
n, k, d = map(int, input().split())
res = "-1"
isFound = False
n *= 10
for i in range(10):
    if (n + i) % k == 0:
        n += i
        isFound = True
        break
if isFound:
    res = str(n) + "0" * (d - 1)
print(res)
