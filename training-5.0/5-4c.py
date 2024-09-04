# https://contest.yandex.ru/contest/59542/problems/C/
n, m = map(int, input().split())
packs = [0] + list(map(int, input().split()))
pref_sum = [0] * (n + 1)
for i in range(0, n + 1):
    pref_sum[i] = (pref_sum[i - 1] + packs[i])
res = []
for i in range(m):
    orc_cnt, orc_sum = map(int, input().split())
    l = 1
    r = n + 1 - orc_cnt
    while l < r:
        m = (l + r) // 2
        if pref_sum[m + orc_cnt - 1] - pref_sum[m - 1] >= orc_sum:
            r = m
        else:
            l = m + 1
    if pref_sum[l + orc_cnt - 1] - pref_sum[l - 1] == orc_sum:
        res.append(l)
    else:
        res.append(-1)
print(*res)
