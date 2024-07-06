# https://contest.yandex.ru/contest/59539/problems/H/
# The second version, clear solution

l, x1, v1, x2, v2 = map(int, input().split())
res = 10 ** 10
for cycle in range(2):
    dX = (x2 - x1 + l) % l
    dV = v1 - v2
    if dV < 0:
        dV = -dV
        dX = (-dX) % l
    if dX == 0:
        res = 0
    if dV != 0:
        res = min(res, dX / dV)
    x2 = (-x2) % l
    v2 = -v2
if res == 10 ** 10:
    print('NO')
else:
    print('YES\n', res)
