# https://contest.yandex.ru/contest/74968/problems/G/
def find(node):
    if parent[node] != node:
        parent[node] = find(parent[node])
    return parent[node]

def union(node1, node2):
    root1, root2 = find(node1), find(node2)
    if root1 == root2:
        return False
    if size[root1] < size[root2]:
        root1, root2 = root2, root1
    parent[root2] = root1
    size[root1] += size[root2]
    return True

import sys
sys.stdin = open('input.txt')
input = sys.stdin.readline
n, m = map(int, input().split())
parent = list(range(n + 1))
size = [1] * (n + 1)
cnt = n
for i in range(1, m + 1):
    x, y = map(int, input().split())
    if union(x, y):
        cnt -= 1
        if cnt == 1:
            print(i)
            break
