# https://contest.yandex.ru/contest/59540/problems/E/
n = int(input())
idx_good = idx_bad = -1
up = []
dn = []
for i in range(n):
    t_up, t_dn = map(int, input().split())
    up.append(t_up)
    dn.append(t_dn)
    if t_up >= t_dn and (idx_good == -1 or t_dn > dn[idx_good]):
        idx_good = i
    if t_up < t_dn and (idx_bad == -1 or t_up > up[idx_bad]):
        idx_bad = i
res = []
max_altitude = 0
for i in range(n):
    if up[i] >= dn[i] and i != idx_good:
        res.append(i + 1)
        max_altitude += up[i] - dn[i]
if idx_good != -1 and idx_bad != -1:
    max_altitude += max(up[idx_good], up[idx_good] - dn[idx_good] + up[idx_bad])
    res.append(idx_good + 1)
    res.append(idx_bad + 1)
elif idx_bad== -1:
    max_altitude += up[idx_good]
    res.append(idx_good + 1)
elif idx_good== -1:
    max_altitude += up[idx_bad]
    res.append(idx_bad + 1)
for i in range(n):
    if up[i] < dn[i] and i != idx_bad:
        res.append(i + 1)
print(max_altitude)
print(*res)
