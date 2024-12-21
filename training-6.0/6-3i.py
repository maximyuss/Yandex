# https://contest.yandex.ru/contest/66794/problems/I/
from collections import deque

reader = open('input.txt', 'r')
n = int(reader.readline())
a, b = map(int, reader.readline().split())
if b < a and not (a == 4 and b == 1) or (a == 1 and b == 4):
    a, b = b, a
order = [a - 1, b - 1]
if b - a == 2:
    is_direct = True
    order += [a % 4, b % 4]
else:
    is_direct = False
    order += [b % 4, (b % 4 + 1) % 4]
rovers = [0] * n
for i in range(n):
    d, t = map(int, reader.readline().split())
    rovers[i] = (t, order.index(d - 1), i)
reader.close()
rovers.sort()
cur_time = rovers[0][0]
cnt, res, it = 0, [0] * n, [0] * 4
for i in range(4):
    rovers.append((1000, i, 101))
    while rovers[it[i]][1] != i: it[i] += 1
while cnt < n:
    a = 0
    for j in range(4):
        if j == 2 and a != 0: break
        if rovers[it[j]][0] <= cur_time:
            res[rovers[it[j]][2]] = cur_time
            it[j] += 1
            while rovers[it[j]][1] != j: it[j] += 1
            n -= 1
            if not is_direct: break
            a += 1
    cur_time += 1
print(*res, sep='\n')
