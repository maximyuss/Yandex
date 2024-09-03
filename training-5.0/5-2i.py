# https://contest.yandex.ru/contest/59540/problems/I/
n = int(input())
ships = []
for _ in range(n):
    row, col = map(int, input().split())
    ships.append((row, col))
ships.sort()
res = n * n
for i in range(1, n + 1):
    count = 0
    for j in range(n):
        count += abs(ships[j][0] - j - 1) + abs(ships[j][1] - i)
    res = min(res, count)
print(res)
