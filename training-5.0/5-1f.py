# https://contest.yandex.ru/contest/59539/problems/F/
# 5-1F

n = int(input())
nums = list(map (int, input().split()))
state = "no odd"
res = ""
for num in nums:
    if state == "no odd":
        if num % 2 == 0:
            res += "+"
        else:
            state = "last odd"
    elif state == "last odd":
        if num % 2 == 0:
            res += "+"
            state = "multiply"
        else:
            res += "x"
    elif state == "multiply":
        res += "x"
print(res)
