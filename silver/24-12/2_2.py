# 二分 + 贪心 只能过一半

from bisect import bisect_left, bisect_right
def tree(l, r):
    return (bisect_right(x,r)-1 - bisect_left(x, l)) + 1
    
T = int(input())
for _ in range(T):
    n,k = map(int,input().split())
    x = list(map(int,input().split()))
    interval = [list(map(int,input().split())) for i in range(k)]
    x.sort()
    interval.sort(key=lambda x:x[1])
    
    # 记录每个区间有多少棵树
    cnt = [0]*k     
    for i in range(k):
        l,r,t = interval[i]
        cnt[i] = tree(l,r)
    
    # 从左往右尝试砍树
    ans = 0
    j = 0
    for pos in x:
        flag = True
        for i in range(j, k):
            l,r,t = interval[i]
            if pos > r:
                j += 1
                continue
            if pos >= l:
                if cnt[i] <= t:     # 当前区间树的数量 >= 要保留的数量才能砍
                    flag = False
                    break        
        if flag:
            for i in range(j, k):       # 确认可以砍了之后，更新各数组
                l,r,t = interval[i]
                if pos > r:
                    j += 1
                    continue
                if pos >= l:
                    cnt[i] -= 1
            ans += 1
    print(ans)
                
            
    
    
    
    