# https://contest.yandex.ru/contest/74964/problems/I/
def solve(p_max, v_total):
    goods.sort(key=lambda x: -x[2])
    length = min(v_total, s + p_max)
    dp = [[(0, -1)] + [(-1, -1)] * length for _ in range(n + 1)]
    v_total = 0
    for i in range(1, n + 1):
        v, m, p, idx = goods[i - 1]
        v_total += v
        length = min(v_total, s + p)
        for j in range(length + 1):
            dp[i][j] = dp[i - 1][j]
        for j in range(length - v + 1):
            if dp[i - 1][j][0] != -1:
                curr = dp[i - 1][j][0]
                if curr + m > dp[i][j + v][0]:
                    dp[i][j + v] = (curr + m, j)

    m_max = (0, 0, 0)
    for i in range(n + 1):
        for j in range(len(dp[0])):
            if dp[i][j][0] > m_max[0]:
                m_max = (dp[i][j][0], i, j)
    res = []
    i, j = m_max[1], m_max[2]
    while j != 0:
        prev = dp[i][j][1]
        if prev == -1:
            break
        if dp[i][j][0] != dp[i - 1][j][0]:
            res.append(goods[i - 1][3])
            j = prev
        i -= 1
        res.sort()
    print(len(res), m_max[0])
    print(*res)

n, s = map(int, input().split())
goods = [0] * (n)
p_max = v_total = 0
for i in range(n):
    v, m, p = map(int, input().split())
    goods[i] = (v, m, p, i + 1)
    p_max = max(p_max, p)
    v_total += v
solve(p_max, v_total)
