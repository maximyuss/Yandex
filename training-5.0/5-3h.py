# https://contest.yandex.ru/contest/59541/problems/H/
n = int(input())
dict1 = {}
dict2 = {}
for i in range(2):
    for _ in range(n):
        x1, y1, x2, y2 = map(int, input().split())
        if (x1, y1) > (x2, y2):
            x1, y1, x2, y2 = x2, y2, x1, y1
        dx, dy = x2 - x1, y2 - y1
        if i == 0:
            if (dx, dy) not in dict1:
                dict1[(dx, dy)] = []
            dict1[(dx, dy)].append((x1, y1))
        else:
            for x, y in dict1.get((dx, dy), []):
                shift_x, shift_y = x1 - x, y1 - y
                dict2[(shift_x, shift_y)] = dict2.get((shift_x, shift_y), 0) + 1
max_shift = 0
for shift in dict2:
    max_shift = max(max_shift, dict2[shift])
print(n - max_shift)
