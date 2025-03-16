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

dis = [[float('inf')]*(k+1) for _ in range(k+1)]        # 记录breed[i]到breed[j]的最短的距离
for i in range(1,k+1): dis[i][i] = 0
inx = [-1] * (k+1)     # 记录每个breed的最优index
inx[b[0]] = 0
for h in range(n):
    for bi in range(1,k+1):
        for bj in range(1,k+1):
            if S[bi][b[h]] and S[b[h]][bj]:
                dis[bi][bj] = min(dis[bi][bj], abs(inx[bi]-b[h])+abs(b[h]-inx[bj]))

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
                
            
    