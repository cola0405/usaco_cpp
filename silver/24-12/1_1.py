t = int(input())
for _ in range(t):
    n = int(input())
    cake = list(map(int, input().split()))
    all = sum(cake)
    E = (n-2)//2
    ans = 0
    
    # build prefix to optimize
    pre = [0]
    for c in cake:
        pre.append(pre[-1]+c)
    
    for left in range(E+1):
        elsie = pre[left] + (pre[-1] - pre[n-(E-left)])
        ans = max(ans, elsie)
    print(all-ans, ans)
