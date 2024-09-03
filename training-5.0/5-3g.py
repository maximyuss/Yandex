# https://contest.yandex.ru/contest/59541/problems/G/
# Slow, but simple solution
n = int(input())
points_lst = []
for _ in range(n):
    points_lst.append(tuple(map(int, input().split())))
points_set = set(points_lst)
x1, y1 = points_lst[0]
res = [(x1, y1 + 1), (x1 + 1, y1), (x1 + 1, y1 + 1)]
for i in range(n):
    for j in range(n):
        if i == j: continue
        x1, y1 = points_lst[i]
        x2, y2 = points_lst[j]
        dx, dy = x2 - x1, y2 - y1
        x3, y3 = x1 + dy, y1 - dx
        x4, y4 = x3 + dx, y3 + dy
        if (x3, y3) in points_set and (x4, y4) in points_set:
            res = []
        if len(res) > 1 and (x3, y3) in points_set:
            res = [(x4, y4)]
        if len(res) > 1 and (x4, y4) in points_set:
            res = [(x3, y3)]
        if len(res) > 2:
            res = [(x3, y3), (x4, y4)]
print(len(res))
for point in res:
    print(*point)
