# https://contest.yandex.ru/contest/66793/problems/G/
def task_6_2_g(n, c, s):
    cnt_mark = cnt_a = cnt_b = res = r = 0
    for l in range(n):
        while r < n:
            if s[r] == 'a':
                cnt_a += 1
            elif s[r] == 'b':
                if cnt_mark + cnt_a <= c:
                    cnt_b += 1
                    cnt_mark += cnt_a
                else:
                    break
            r += 1
        res = max(res, r - l)
        if s[l] == 'a':
            cnt_a -= 1
            cnt_mark -= cnt_b
        elif s[l] == 'b':
            cnt_b -= 1
    return res


n, c = map(int, input().split())
s = input()
print(task_6_2_g(n, c, s))
