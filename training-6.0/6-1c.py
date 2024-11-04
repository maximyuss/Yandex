# https://contest.yandex.ru/contest/66792/problems/C/
def transform(m):
    rows = len(m[0]) if m != [] else 0
    blank_row = '.' * rows
    t = [blank_row, *m, blank_row]
    t = [s for i, s in enumerate(t[1:]) if s != t[i]]  # Removing duplicate lines
    if t != [] and t[-1] == blank_row: t.pop()
    t = [''.join(s) for s in [*zip(*t)]]  # Transpose a list
    return t

def task_6_с(board):
    shrink_board = transform(transform(board))
    if shrink_board == []: shrink_board = '.'
    code = int(''.join(''.join('0' if char == '.' else '1' for char in s) for s in shrink_board), 2)
    dict = {1: 'I', 11: 'L', 59: 'C', 381: 'H', 495: 'O', 3964: 'P'}
    if code in dict:
        return dict[code]
    return 'X'

n = int(input())
board = [''] * n
for i in range(n):
    board[i] = input()
print(task_6_с(board))
