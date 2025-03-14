# https://contest.yandex.ru/contest/66795/problems/F/
import sys
sys.setrecursionlimit(300000)

def dfs(idx):
    size = 1
    for node in tree[idx]:
        curr_money, curr_size = dfs(node)
        res[idx] += curr_money + curr_size
        size += curr_size
    res[idx] += 1
    return res[idx], size

with open('input.txt', 'r') as reader:
    n = int(reader.readline())
    bosses = list(map(int, reader.readline().split()))
tree = [[] for _ in range(n)]
res = [0] * n
for i in range(n - 1):
    tree[bosses[i] - 1].append(i + 1)
dfs(0)
print(*res)
