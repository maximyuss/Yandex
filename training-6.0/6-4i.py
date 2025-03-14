# https://contest.yandex.ru/contest/66795/problems/I/
import sys

sys.setrecursionlimit(500000)

def calc_subtrees(num, cur, parent):
    if len(edges[cur]) == 1 and parent != 0: return
    max1 = max2 = max_subt = -1
    for neib in edges[cur]:
        if neib == parent: continue
        if num == 0 or (num == 1 and is_main_path[neib]):
            calc_subtrees(num, neib, cur)
        max_subt = max(max_subt, dp_subt[neib][num])
        if dp_lens[neib][0] > max1:
            max2 = max1
            max1 = dp_lens[neib][0]
        elif dp_lens[neib][0] > max2:
            max2 = dp_lens[neib][0]
    dp_subt[cur][num] = max(max_subt, max1 + max2 + 2)
    dp_lens[cur][0] = max1 + 1
    dp_lens[cur][1] = max2 + 1

def find_ends():
    def dfs(cur, parent):
        nonlocal sub_res
        levels[cur] = levels[parent] + 1
        if (levels[cur] > sub_res[0]):
            sub_res = (levels[cur], cur)
        for neib in edges[cur]:
            if neib == parent: continue
            dfs(neib, cur)

    levels = [0] * (n + 1)
    sub_res = (0, 0)
    res = [0, 0]
    dfs(1, 0)
    res[0] = sub_res[1]
    sub_res = (0, 0)
    dfs(res[0], 0)
    res[1] = sub_res[1]
    return res

def mark_main_path(cur, parent):
    if len(edges[cur]) == 1 and parent != 0:
        return
    idx_max = lens_max = -1
    for neib in edges[cur]:
        if neib == parent: continue
        if dp_lens[neib][0] <= lens_max: continue
        idx_max = neib
        lens_max = dp_lens[neib][0]
    is_main_path[idx_max] = True
    mark_main_path(idx_max, cur)

reader = open('input.txt', 'r')
n = int(reader.readline())
edges = [[] for _ in range(n + 1)]
for _ in range(n - 1):
    a, b = map(int, reader.readline().split())
    edges[a].append(b)
    edges[b].append(a)
reader.close()

ends = find_ends()
dp_subt = [[0, 0] for _ in range(n + 1)]
dp_lens = [[0, 0] for _ in range(n + 1)]
is_main_path = [False] * (n + 1)
is_main_path[ends[0]], is_main_path[ends[1]] = True, True

calc_subtrees(0, ends[0], 0)
mark_main_path(ends[1], 0)
dp_lens[ends[0]] = [0, 0]
calc_subtrees(1, ends[1], 0)

cur = ends[0]
res = parent = 0
while cur != ends[1]:
    for neib in edges[cur]:
        if neib == parent: continue
        if is_main_path[neib]:
            a = dp_subt[neib][0]
            b = dp_subt[cur][1]
            next = neib
        else:
            a = dp_subt[ends[0]][0]
            b = dp_subt[neib][0]
        res = max(res, a * b)
    parent = cur
    cur = next
print(res)
