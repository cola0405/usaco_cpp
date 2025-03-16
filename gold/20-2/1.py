# topological sort

import sys
from collections import defaultdict,deque

sys.stdin = open('timeline.in', 'r')
sys.stdout = open('timeline.out', 'w')

n,m,c = map(int,input().split())
S = list(map(int, input().split()))
ab = defaultdict(list)
pre = [0]*(n+1)     # 前置session数量
for _ in range(c):
    a,b,x = map(int,input().split())
    ab[a].append((b,x))
    pre[b] += 1

q = []
for i in range(1,n+1):
    if pre[i] == 0: q.append(i)

while q:
    a = q.pop()
    for b,x in ab[a]:
        pre[b] -= 1
        S[b-1] = max(S[b-1], S[a-1]+x)  # 应该取所有可能时间的最大值
        if pre[b] == 0: q.append(b)     # 前置数量为 0时加入队列

for t in S: print(t)



