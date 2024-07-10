# https://contest.yandex.ru/contest/59540/problems/A/

k = int(input())
min_x, min_y = map(int, input().split())
max_x, max_y = min_x, min_y
for i in range(k - 1):
    x, y = map(int, input().split())
    min_x = min(min_x, x)
    min_y = min(min_y, y)
    max_x = max(max_x, x)
    max_y = max(max_y, y)
print(min_x, min_y, max_x, max_y)
