# https://contest.yandex.ru/contest/59541/problems/D/
n, k = map(int, input().split())
nums = list(map(int, input().split()))
is_find = False
window = set()
for i in range(n):
    if nums[i] in window:
        is_find = True
        break
    if i >= k:
        window.remove(nums[i - k])
    window.add(nums[i])
if is_find:
    print("YES")
else:
    print("NO")
