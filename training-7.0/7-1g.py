# https://contest.yandex.ru/contest/74964/problems/G/
import sys

def solve(max_len: int):
    max_len = max_len // 2 + 1
    dp = [[0] + [-1] * max_len for _ in range(k + 1)]
    for i in range(n):
        length, color = bricks[i]
        for j in range(max_len - length, -1, -1):
            next = j + length
            if dp[color][next] == -1 and dp[color][j] != -1:
                dp[color][next] = i

    res = []
    for i in range(1, max_len):
        is_good = True
        for color in range(1, k + 1):
            if dp[color][i] == -1:
                is_good = False
                break
        if is_good:
            print('YES')
            for color in range(1, k + 1):
                j = i
                while j != 0:
                    res.append(dp[color][j] + 1)
                    j -= bricks[dp[color][j]][0]
            print(*res)
            return
    else:
        print('NO')

sys.stdin = open('input.txt', 'r')
n, k = map(int, input().split())
bricks = [(0, 0)] * n
max_len = 0
for i in range(n):
    length, color = map(int, input().split())
    bricks[i] = (length, color)
    if color == 1:
        max_len += length
solve(max_len)
