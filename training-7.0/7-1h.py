# https://contest.yandex.ru/contest/74964/problems/H/
n = int(input())
orders = []
is_any_odd = False
for i in range(n):
    s = input()
    is_odd = len(s) % 2 == 1
    orders.append([0, 0, is_odd])
    is_any_odd = is_any_odd or is_odd
    for j in range(len(s)):
        if s[j] == 'S':
            orders[i][j % 2] += 1

res = 0
if not is_any_odd:
    for order in orders:
        res += order[0]
    print(res)
else:
    odd_orders = []
    for order in orders:
        if not order[2]:
            res += max(order[0], order[1])
        else:
            odd_orders.append(order)
    odd_orders.sort(key=lambda x: x[0] - x[1])
    left, right = 0, len(odd_orders) - 1
    is_odd = 0
    while left <= right:
        if is_odd:
            res += odd_orders[left][1]
            left += 1
        else:
            res += odd_orders[right][0]
            right -= 1
        is_odd = 1 - is_odd
    print(res)
