# dijastra（限制版）

# Ps：优先队列排序不是找最短的边，而是应该找当前最小的min_cost[i]（到 i节点的最小花费） 进行贪心

# https://usaco.org/index.php?page=viewproblem2&cpid=969
# https://www.luogu.com.cn/problem/P5837

from collections import defaultdict
import heapq
import sys
sys.stdin = open('pump.in', 'r')
sys.stdout = open('pump.out', 'w')

n,m = map(int,input().split())
g = defaultdict(list)
s = set()
for _ in range(m):
    a,b,c,f = map(int,input().split())
    g[a].append((b,c,f))
    g[b].append((a,c,f))
    s.add(f)

ans = 0
for f in s:
    vis = [0]*(n+1)
    q = [(0,1)]       # (min_cost_to_current_node, current_node)
    min_cost = [float('inf')]*(n+1)
    min_cost[1] = 0
    while q:           # q 的作用: 保存当前的生成树的状态
        c,node = heapq.heappop(q)
        # dijastra贪心的前提下，到 node的最短距离早已确定，不会之后更新的
        # 换句话说，每个节点只会被访问一次
        vis[node] = 1
        for nxt, cost, flow in g[node]:     # 把新节点扩展的合法边加入优先队列
            if not vis[nxt] and flow >= f and c + cost < min_cost[nxt]:
                min_cost[nxt] = c + cost                   # 在这里更新 min_cost那在优先队列中就不用保存 last节点
                heapq.heappush(q, (min_cost[nxt], nxt))    # min_cost[nxt] 是用于优先队列排序的
    ans = max(ans, f*1e6/min_cost[n])
print(int(ans))


