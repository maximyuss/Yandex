# https://contest.yandex.ru/contest/74967/problems/H/
def fenwick_add(x, y, z, delta):
    xi = x + 1
    while xi <= n:
        yi = y + 1
        while yi <= n:
            zi = z + 1
            while zi <= n:
                fenwick[xi][yi][zi] += delta
                zi += zi & -zi
            yi += yi & -yi
        xi += xi & -xi

def fenwick_sum(x, y, z):
    res = 0
    xi = x + 1
    while xi > 0:
        yi = y + 1
        while yi > 0:
            zi = z + 1
            while zi > 0:
                res += fenwick[xi][yi][zi]
                zi -= zi & -zi
            yi -= yi & -yi
        xi -= xi & -xi
    return res

def cube_sum(x1, y1, z1, x2, y2, z2):
    return (
        fenwick_sum(x2, y2, z2) - 
        fenwick_sum(x1 - 1, y2, z2) -
        fenwick_sum(x2, y1 - 1, z2) -
        fenwick_sum(x2, y2, z1 - 1) +
        fenwick_sum(x1 - 1, y1 - 1, z2) +
        fenwick_sum(x1 - 1, y2, z1 - 1) +
        fenwick_sum(x2, y1 - 1, z1 - 1) -
        fenwick_sum(x1 - 1, y1 - 1, z1 - 1)
    )

import sys
n = int(input())
fenwick = [[[0] * (n + 1) for _ in range(n + 1)] for _ in range(n + 1)]
output = []
while True:
    args = list(map(int, input().split()))
    if args[0] == 1:
        x, y, z, k = args[1:]
        fenwick_add(x, y, z, k)
    elif args[0] == 2:
        x1, y1, z1, x2, y2, z2 = args[1:]
        output.append(str(cube_sum(x1, y1, z1, x2, y2, z2)))
    elif args[0] == 3:
        break
sys.stdout.write("\n".join(output) + "\n")
