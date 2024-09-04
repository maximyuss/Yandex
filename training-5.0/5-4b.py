# https://contest.yandex.ru/contest/59542/problems/B/
def solve(k):
    if k < 2: return k
    tmp = k
    res = 0
    k_2 = k // 2 + 1
    for i in range(1, k_2):
        res += 2 * i * tmp
        tmp -= 1
    if k % 2 == 1:
        res += (k_2) * (k_2)
    res += k * (k + 1) // 2
    return res - 1


n = int(input())
l = 0
r = min(n, 2000000)
while l < r:
    m = (l + r + 1) // 2
    if solve(m) <= n:
        l = m
    else:
        r = m - 1
print(l)
