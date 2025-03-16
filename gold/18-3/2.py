# 拓扑排序判断环 + 二分 + （拓扑排序 + 优先队列得出最小字典序）

from collections import defaultdict,deque
import sys, heapq
sys.stdin = open('milkorder.in', 'r')
sys.stdout = open('milkorder.out', 'w')

def is_cycle(k):      # 拓扑排序判断是否构成环 (环中的节点无法通过拓扑排序访问)
    g = defaultdict(list)
    in_degree = [0]*(n+1)
    for i in range(k):
        order = orders[i]
        for j in range(1, len(order)-1):
            g[order[j]].append(order[j+1])
            in_degree[order[j+1]] += 1

    vis = [0]*(n+1)
    q = deque()
    for i in range(1, n+1):
        if in_degree[i] == 0: q.append(i)

    while q:
        node = q.popleft()
        vis[node] = 1
        for nxt in g[node]:
            in_degree[nxt] -= 1
            if in_degree[nxt] == 0: q.append(nxt)
    return sum(vis) == n

n, m = map(int, input().split())
orders = [list(map(int, input().split())) for _ in range(m)]

l,r = 0,m-1               # 二分搜索看最多能取前 X个条件 (upper-bound)
while l<r:
    mid = (l+r+1)//2
    if is_cycle(mid):     # 判断是否成环
        l = mid
    else:
        r = mid-1

# 根据前面获取的合理的最大 X来进行拓扑排序，得到合理序列
g = defaultdict(list)
for i in range(l):
    order = orders[i]
    for j in range(1, len(order)-1):
        g[order[j]].append(order[j+1])

in_degree = [0]*(n+1)
for i in range(l):
    order = orders[i]
    for j in range(2, len(order)):
        in_degree[order[j]] += 1

q = []
for i in range(1, n+1):
    if in_degree[i] == 0: q.append(i)

ans = []
while q:
    x = heapq.heappop(q)       # 优先队列得出最小字典序
    ans.append(str(x))
    for nxt in g[x]:
        in_degree[nxt] -= 1
        if in_degree[nxt] == 0: heapq.heappush(q, nxt)
print(' '.join(ans))