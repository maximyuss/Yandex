# https://contest.yandex.ru/contest/66794/problems/F/
from collections import deque

pairs = {'[': ']', ']': '[', '(': ')', ')': '('}
st = deque()
w = {}

reader = open('input.txt', 'r')
n = int(reader.readline())
s = reader.readline().rstrip()
for i in range(4):
    w[s[i]] = i
min_open_idx = min(w['('], w['['])
min_open = s[min_open_idx]
s = reader.readline().rstrip()
reader.close()

for ch in s:
    if ch == '(' or ch == '[':
        st.append(ch)
    else:
        st.pop()
len_empty = n - len(s) - len(st)
while len_empty:
    top_idx = 1000
    if len(st):
        top = st[-1]
        top_idx = w[pairs[top]]
    if top_idx < min_open_idx:
        s += pairs[top]
        st.pop()
    else:
        st.append(min_open)
        s += min_open
        len_empty -= 2
while len(st):
    top = st.pop()
    s += pairs[top]
print(s)
