# https://contest.yandex.ru/contest/59540/problems/D/

board = [[False] * 10 for i in range(10)]
shift = [[-1, 0], [0, -1], [1, 0], [0, 1]]
res = 0
n = int(input())
for i in range(n):
    x, y = map(int, input().split())
    board[x][y] = True
    res += 4
    for j in range(4):
        if board[x + shift[j][0]][y + shift[j][1]]:
            res -= 2
print(res)
