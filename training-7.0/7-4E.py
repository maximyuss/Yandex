# https://contest.yandex.ru/contest/74968/problems/E/
class Node:
    def __init__(self, value, idx, next=None, prev=None):
        self.value = value
        self.idx = idx
        self.dismiss = 0
        self.next = next
        self.prev = prev

class DLList:
    size: int
    head: Node
    tail: Node

    def __init__(self):
        self.head = self.tail = None

    def push_back(self, value, idx):
        node = Node(value, idx, None, self.tail)
        if not self.head:
            self.head = self.tail = node
        else:
            node.prev = self.tail
            self.tail.next = node
            self.tail = node

    def delete(self, node: Node):
        curr_dismiss = node.dismiss + 1
        res[node.idx] = curr_dismiss
        node.next.dismiss = max(node.next.dismiss, curr_dismiss)
        node.prev.dismiss = max(node.prev.dismiss, curr_dismiss)
        node.next.prev, node.prev.next = node.prev, node.next

import sys
people = DLList()
sys.stdin = open('input.txt')
n = int(input())
a = list(map(int, input().split()))
res = [0] * n
for i in range(n):
    people.push_back(a[i], i)
people.tail.next = people.head
people.head.prev = people.tail
curr: Node = people.head
last_update = people.head.idx
while True:
    if curr.prev.value > curr.value < curr.next.value and curr.next != curr.prev:
        people.delete(curr)
        curr = curr.prev
        last_update = curr.idx
    else:
        curr = curr.next
        if curr.idx == last_update:
            break
print(*res)
