# https://contest.yandex.ru/contest/59539/problems/D/
# 5-1D

# Shifts table, 0: Rook, 1: Bishop
di = [[0, 0, 1, -1], [1, 1, -1, -1]]
dj = [[1, -1, 0, 0], [1, -1, 1, -1]]

board = [list('#') * 10]
for i in range(8):
    board.append(['#'] + list(input()) + ['#'])
board.append(list('#') * 10)
for i in range(1, 10):
    for j in range(1, 10):
        if board[i][j] == 'R' or board[i][j] == 'B':
            if board[i][j] == 'R':
                figure = 0
            else:
                figure = 1
            for shift in range(4):
                tmpI, tmpJ = i + di[figure][shift], j + dj[figure][shift]
                while board[tmpI][tmpJ] == '*' or board[tmpI][tmpJ] == '.':
                    board[tmpI][tmpJ] = '.'
                    tmpI += di[figure][shift]
                    tmpJ += dj[figure][shift]
res = 0
for row in board:
    for cell in row:
        if cell == '*':
            res += 1
print(res)
