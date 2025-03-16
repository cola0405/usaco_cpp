# bfs + 子树问题

'''
主要解题思路：先假设每个出口都放一个农民，然后让农民开始往根节点走
一直走到 "相遇节点" 才停下来 （"相遇节点" 到根节点和到子树最近叶子节点的距离相等）
然后再看 Bessie 能够遇见几个农民 —— 这个农民数量就是保证拦截住Bessie所需的最少的农民数量

算法步骤：
1.bfs先计算根节点到节点的距离
2.假设所有出口都放一个农民，然后使用 bfs 向上扩散到 "相遇节点"
3.从根节点开始 bfs 统计总共会与多少个农民相遇，其数量就是答案
'''

import sys
from collections import defaultdict,deque

sys.stdin = open('atlarge.in', 'r')
sys.stdout = open('atlarge.out', 'w')

n,k = map(int, input().split())
g = defaultdict(list)
in_degree = [0]*(n+1)       # 每个节点的入度
for _ in range(n-1):
    a,b = map(int, input().split())
    g[a].append(b)
    g[b].append(a)
    in_degree[a] += 1
    in_degree[b] += 1

# bfs 统计根节点到每个节点的距离
dis = [0]*(1+n)
vis = [0]*(1+n)
q = deque([k])
d = 0
while q:
    size = len(q)
    for _ in range(size):
        node = q.popleft()
        dis[node] = d
        vis[node] = 1
        for nxt in g[node]:
            if not vis[nxt]: q.append(nxt)
    d += 1

# bfs 模拟农民的抓捕，直到 "遇见节点"
vis = [0]*(n+1)     # 用于标记农民走过的路
q = deque()
for node in range(1,n+1):
    if in_degree[node] == 1:
        q.append(node)
d = 0
while q:
    size = len(q)
    for _ in range(size):
        node = q.popleft()
        vis[node] = 1
        for nxt in g[node]:
            if vis[nxt] or dis[nxt] < d+1: continue
            q.append(nxt)
    d += 1

# Bessie 往外bfs，统计遇到的农民数量
ans = 0
vis1 = [0]*(n+1)    # 确保 bfs不会死循环
q = deque([k])
while q:
    size = len(q)
    for _ in range(size):
        node = q.popleft()
        vis1[node] = 1
        for nxt in g[node]:
            if vis1[nxt]: continue
            if vis[nxt]: ans += 1       # 这个 vis数组是第二次 bfs留下的标记
            else: q.append(nxt)
print(ans)