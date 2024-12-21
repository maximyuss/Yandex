# https://contest.yandex.ru/contest/66794/problems/H/
class stask_with_summ:
    def __init__(self):
        self._store = []
        self._sums = [0]
        self._cnt = 0
        self._total = 0

    def push(self, val):
        self._store.append(val)
        self._total += val
        self._sums.append(self._total)
        self._cnt += 1

    def pop(self):
        val = self._store.pop()
        self._sums.pop()
        self._total -= val
        self._cnt -= 1
        return val

    def sum(self, k):
        return self._total - self._sums[self._cnt - k];


stack = stask_with_summ()
n = int(input())
res = []
for _ in range(n):
    arg = input()
    if arg[0] == '+':
        stack.push(int(arg[1:]))
    elif arg[0] == '-':
        res.append(stack.pop())
    elif arg[0] == '?':
        k = int(arg[1:])
        res.append(stack.sum(k))
print(*res, sep='\n')
