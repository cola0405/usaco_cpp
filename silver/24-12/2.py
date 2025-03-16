# 二分 + 贪心 + 优先队列

# 贪心解释：
# 对于区间 [l,r] 我们优先砍左边的树，目的是为了让右边没砍的树缓解后面的限制

from bisect import bisect_left, bisect_right
import heapq
def tree(l, r):     # 返回在l和r之间的树的数量
    return (bisect_right(x,r)-1 - bisect_left(x, l)) + 1

T = int(input())
for _ in range(T):
    events = []
    n,k = map(int,input().split())
    x = list(map(int,input().split()))      # 树的位置
    interval = [list(map(int,input().split())) for i in range(k)]  # 限制的区间
    for t in x:
        events.append((t, 0, 0, 0))     # (树的位置, 0, 0, 0) 其他是填充位
    for l,r,remain in interval:
        events.append((l, -1, r, tree(l,r) - remain))    # (left, -1表示当前item是限制, right, 可以砍的树的数量) 0表示当前item是树

    events.sort()
    ans = 0
    pq = []     # 只保留限制 (区间右端点往左最多能砍的树的数量，区间右端点)
    for l,t,r,cut in events:
        if t == -1:         # -1 表示当前item是限制
            heapq.heappush(pq, (ans + cut, r))
        else:               # 进入else 表示当前item是树
            while pq and pq[0][1] < l:  # 如果限制的右端点小于树的位置，那么这个限制就可以pop出去了
                heapq.heappop(pq)
            ans += len(pq)==0 or pq[0][0] > ans     # 如果pq为空则表示没有限制；或者当前能砍的树 > 已砍的树，那把当前这棵树砍掉
    print(ans)
