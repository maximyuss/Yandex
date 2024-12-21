# https://contest.yandex.ru/contest/66793/problems/H/
def task_6_2_h(n, nums):
    pref = [0] * n
    peoples = nums[0]
    for i in range(1, n):
        pref[i] = pref[i - 1] + peoples
        peoples += nums[i]
    suff, peoples, res = 0, nums[n - 1], pref[n - 1]
    for i in range(n - 2, -1, -1):
        suff += peoples
        peoples += nums[i]
        curr = pref[i] + suff
        res = min(res, curr)
    return res

n =  int(input())
nums = list(map(int, input().split()))
print(task_6_2_h(n, nums))
