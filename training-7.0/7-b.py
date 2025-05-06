# https://contest.yandex.ru/contest/74964/problems/B/
t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    prev_break = 0
    cur_min = a[0]
    res = []
    for i in range(n):
        cur_min = min(cur_min, a[i])
        if prev_break + cur_min <= i:
            res.append(i - prev_break)
            prev_break = i
            cur_min = a[i]
    res.append(n - prev_break)
    print(len(res))
    print(*res)
