# https://contest.yandex.ru/contest/66794/problems/J/
from collections import deque

reader = open('input.txt', 'r')
n, height = map(int, reader.readline().split())
arr = sorted(zip(map(int, reader.readline().split()), map(int, reader.readline().split())))
arr.append((float('inf'), 0))
reader.close()
dq = deque([(0, 0)])
discomfort, res, l, r = 0, float('inf'), 0, 1
last_height, sum_width = arr[0]
while l < n:
    while r <= n and sum_width < height:
        discomfort = arr[r][0] - last_height
        while len(dq) and dq[-1][1] <= discomfort:
            dq.pop()
        sum_width += arr[r][1]
        dq.append((r, discomfort))
        last_height = arr[r][0]
        r += 1
    res = min(res, dq[0][1])
    if res == 0: break
    sum_width -= arr[l][1]
    l += 1
    if l >= dq[0][0]: dq.popleft();
print(res)
