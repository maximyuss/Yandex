# https://contest.yandex.ru/contest/74964/problems/C/
target = int(input())
nums = list(map(int, input().split()))
for i in range(1, 31):
    nums[i] = max(nums[i], nums[i - 1] * 2)
cost = 0
res = float('inf')
for i in range(30, -1, -1):
    if target <= nums[i]:
        res = min(res, cost + 2**i)
    else:
        cost += 2**i
        target -= nums[i]
print(res)
