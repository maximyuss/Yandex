# https://contest.yandex.ru/contest/74967/problems/I/
def calcCountRedundantBits(n):
    for i in range(n):
        if (2**i >= n + i + 1):
            return i

def insertRedundantBits(data: str, k: int) -> str:
    n = len(data)
    m = n + k
    res = []
    j = 0
    for i in range(1, m + 1):
        if (i & (i - 1)) == 0:
            res.append('0')
        else:
            res.append(data[j])
            j += 1
    return ''.join(res)

def calcParityBits(arr: str, k: int) -> str:
    res = list(arr)
    n = len(res)
    for i in range(k):
        pos = 1 << i
        parity = 0
        for j in range(1, n + 1):
            if j & pos:
                parity ^= int(arr[j - 1])
        res[pos - 1] = str(parity)
    return ''.join(res)

def extractData(arr: str) -> str:
    n = len(arr)
    k = 0
    while (1 << k) <= n:
        k += 1
    res = list(arr)
    error = 0
    for i in range(k):
        pos = 1 << i
        parity = 0
        for j in range(1, n + 1):
            if j & pos:
                parity ^= int(res[j - 1])
        if parity == 1:
            error += pos
    if error > 0 and 1 <= error <= n:
        res[error - 1] = '0' if res[error - 1] == '1' else '1'
    data = []
    for i in range(1, n + 1):
        if (i & (i - 1)) != 0:
            data.append(res[i - 1])
    return ''.join(data)

command = input()
data = input()
if command == '1':
    n = len(data)
    k = calcCountRedundantBits(n)
    res = insertRedundantBits(data, k)
    res = calcParityBits(res, k)
else:
    res = extractData(data)
print(res)
