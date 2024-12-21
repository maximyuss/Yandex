# https://contest.yandex.ru/contest/66793/problems/F/
def task_6_2_f(n, nums):
    res, M = 0, 1000000007
    suff = [0] * n
    summ = nums[n - 1]
    for i in range(n - 2, 0, -1):
        suff[i] = summ * nums[i] + suff[i + 1]
        summ += nums[i]
    for l in range(n - 2):
        calc = nums[l] * suff[l + 1]
        res = res + calc
    return res % M

n = int(input())
nums = list(map(int, input().split()))
print(task_6_2_f(n, nums))
