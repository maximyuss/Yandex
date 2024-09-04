# https://contest.yandex.ru/contest/59542/problems/A/
def bin_search(nums, target):
    l, r = 0, len(nums)
    while l < r:
        m = (l + r) // 2
        if nums[m] >= target:
            r = m
        else:
            l = m + 1
    return l


n = int(input())
nums = list(map(int, input().split()))
nums.sort()
nums.append(1000000001)
k = int(input())
res = []
for i in range(k):
    l, r = map(int, input().split())
    idx_l = bin_search(nums, l)
    idx_r = bin_search(nums, r + 1)
    res.append(idx_r - idx_l)
print(*res)
