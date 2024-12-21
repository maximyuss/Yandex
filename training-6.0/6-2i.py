# https://contest.yandex.ru/contest/66793/problems/I/
n = int(input())
a = list(map(int, input().split()))
b = list(map(int, input().split()))
c = list(map(int, input().split()))
d, arr = [0] * n, [[0] * n, [0] * n]
for i in range(n):
    arr[0][i] = (a[i], b[i], n - i)
    arr[1][i] = (b[i], a[i], n - i)
    d[i] = i
arr[0].sort()
arr[1].sort()
it = [n - 1, n - 1]
for i in range(n):
    x = c[i]
    while it[x] >= -1 and d[n - arr[x][it[x]][2]] == -1:
        it[x] -= 1
    curr = n - arr[x][it[x]][2]
    it[x] -= 1
    c[i] = curr + 1
    d[curr] = -1
print(*c)
