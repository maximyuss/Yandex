#https://contest.yandex.ru/contest/59539/problems/A/
#5-1A
p, v = map(int, input().split())
q, m = map(int, input().split())
minV, maxV = p - v, p + v
minM, maxM = q - m, q + m
if max(minV, minM) <= min(maxV, maxM):
    print(max(maxV, maxM) - min(minV, minM) + 1)
else:
    print((2 * v + 1) + (2 * m + 1))
