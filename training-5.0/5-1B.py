#https://contest.yandex.ru/contest/59539/problems/B/
#5-1B
q11, q21 = map(int, input().split(':'))
q12, q22 = map(int, input().split(':'))
home = int(input())
if home == 1:
    score1 = q11 * 100 + q12 * 101
    score2 = q21 * 101 + q22 * 100
    print(max(0, (score2 - score1 + 101) // 101))
else:
    score1 = q11 * 101 + q12 * 100
    score2 = q21 * 100 + q22 * 101
    print(max(0, (score2 - score1 + 100) // 100))
