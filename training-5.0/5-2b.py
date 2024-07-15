# https://contest.yandex.ru/contest/59540/problems/B/

n, k = map(int, input().split())
prices = list(map(int, input().split()))
res = 0
if n > 1:
    for i in range(k): prices.append(prices[-1])
    local_max = prices[0]
    for i in range(0, n - 1):
        new_index = i + k
        if prices[i] == local_max:
            local_max = max(prices[i + 1:new_index + 1])
        else:
            local_max = max(local_max, prices[new_index])
        res = max(res, local_max - prices[i])
print(res)
