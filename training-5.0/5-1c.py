#https://contest.yandex.ru/contest/59539/problems/C/
#5-1C
n = int(input())
res = 0
for i in range(n):
    a = int(input())
    res += a // 4
    remain = a % 4
    if remain == 1 or remain == 2: res += remain
    if remain == 3: res += 2
print(res)
