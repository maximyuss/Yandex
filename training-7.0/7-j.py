# https://contest.yandex.ru/contest/74964/problems/J/
n, d = map(int, input().split())
events = [(0, 0)] * n
max_m = cnt_days = 0
for idx in range(n):
    name, m = input().split()
    m = int(m)
    events[idx] = (m, name)
    max_m = max(max_m, m)

MAX = 10**7 + 1
indices = [i for i, _ in sorted(enumerate(events), key=lambda x: x[1][0])]
dp = [0] + [MAX] * events[indices[-1]][0]
m_max = 0
idx_end = n
cnt_days = 0
if events[indices[0]][0] > d:
    idx_end = 0
elif events[indices[-1]][0] <= d:
    cnt_days = n
else:
    for i, idx in enumerate(indices):
        m = events[idx][0]
        if m <= d:
            days = 1
        else:
            days = min(dp[m - d:m + 1]) + 1
            if days > MAX:
                idx_end = i
                break
        cnt_days += days
        m_max = min(m_max + m, events[indices[-1]][0] - d + 1)
        for j in range(m_max - m, -1, -1):
            if dp[j] != MAX and dp[j + m] > dp[j] + days:
                dp[j + m] = dp[j] + days
res = sorted(events[i][1] for i in indices[:idx_end])
print(len(res), cnt_days)
print(*res, sep='\n')
