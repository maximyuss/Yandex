# https://contest.yandex.ru/contest/59541/problems/F/
dict = set(input().split())
res = []
for word in input().split():
    for i in range(1, min(101, len(word))):
        part = word[:i]
        if part in dict:
            res.append(part)
            break
    else:
        res.append(word)
print(*res)
