# https://contest.yandex.ru/contest/59541/problems/E/
n1 = int(input())
s1 = set(map(int, input().split()))
n2 = int(input())
s2 = set(map(int, input().split()))
n3 = int(input())
s3 = set(map(int, input().split()))
res = s1 & s2
merged_s1_s2 = s1.union(s2)
res = res.union(merged_s1_s2 & s3)
print(*sorted(res))
