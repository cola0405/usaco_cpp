# 对于某个品种的牛，它肯定要不往左找最近的，要不往右找最近的
# 我们可以基于此建边，每个牛最多有两天边，那么总边数就是 2*n*k
# 使用SPFA求最短路即可

'''
12 23 35 54
1 2 3 2 5 3 4

最优解: 1 -> 2 -> 3 -> 5 -> 4
可以证明不是单纯看最右
单纯看最左也不行，考虑此测试用例: 1 5 2 3 2 5 3 4
(选左边的5也不好使)

'''

from collections import defaultdict, deque
n,k = map(int, input().split())
b = list(map(int, input().split()))
S = [[int(c) for c in input()] for _ in range(k)]

d = defaultdict(list)       # record the index of each breed
for i in range(n):
    d[b[i]].append(i)

dis = [1e9 for _ in range(n)]
dis[0] = 0
q = deque([0])  # index of the node
vis = [0]*(k+1)
while q:
    i = q.popleft()
    if vis[b[i]]: continue
    vis[b[i]] = 1
    for nxt in range(1,k+1):    # next breed
        if S[b[i]-1][nxt-1] and len(d[nxt]) > 0:
            l,r = 0,len(d[nxt])-1
            while l+1 < len(d[nxt]) and d[nxt][l+1] < i:
                l += 1
            while r-1 >= 0 and d[nxt][r-1] > i:
                r -= 1

            if i - d[nxt][l] < d[nxt][r] - i:
                dis[nxt] = min(dis[nxt], dis[i] + abs(i - d[nxt][l]))
                q.append(d[nxt][l])
            else:
                dis[nxt] = min(dis[nxt], dis[i] + abs(d[nxt][r] - i))
                q.append(d[nxt][r])
print(dis[-1])
                
            
    