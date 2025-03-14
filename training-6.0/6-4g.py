# https://contest.yandex.ru/contest/66795/problems/G/
import sys
sys.setrecursionlimit(2000000)

def solve(idx, is_root, parent):
    global res, is_error
    if is_error:
        return 0
    if is_root and len(birds[idx]) == 1 and len(birds[birds[idx][0]]) > 1:
        solve(birds[idx][0], True, -1)
        return
    visited[idx] = True
    cnt_social_friends = 0
    subtree_size = 1
    for friend in birds[idx]:
        if visited[friend] and friend != parent:
            is_error = True
        elif not visited[friend]:
            curr_size = solve(friend, False, idx)
            subtree_size += curr_size
            if curr_size >= 2:
                cnt_social_friends += 1
            if (is_root and cnt_social_friends > 2) or (not is_root and cnt_social_friends > 1):
                is_error = True
    cnt_unsocial_friends = len(birds[idx]) - cnt_social_friends - 1 + int(is_root)
    res = (res * factorial[cnt_unsocial_friends]) % k
    if is_root:
        res = (res * 2) % k
        if (cnt_unsocial_friends > 0 and cnt_social_friends > 0) or cnt_social_friends == 2:
            res = (res * 2) % k
    return subtree_size

reader = open('input.txt', 'r')
n, m, k = map(int, reader.readline().split())
if m > n - 1:
    reader.close()
    print(0)
else:
    birds = [[] for _ in range(n + 1)]
    for _ in range(m):
        a, b = map(int, reader.readline().split())
        birds[a].append(b)
        birds[b].append(a)
    reader.close()
    factorial = [1] * (n + 1)
    for i in range(2, n + 1):
        factorial[i] = factorial[i - 1] * i % k
    res = 1
    is_error = False
    trees = lonely = 0
    visited = [False] * (n + 1)

    for i in range(1, n + 1):
        if is_error:
            break
        if not visited[i] and len(birds[i]) > 0:
            trees += 1
            solve(i, True, -1)
        if len(birds[i]) == 0:
            lonely += 1
    if is_error:
        print(0)
    else:
        res = (res * factorial[trees]) % k
        not_lonely = n - lonely
        for i in range(lonely):
            res = (res * (2 + not_lonely + i)) % k
        print(res)
