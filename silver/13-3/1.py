# 贪心
# https://usaco.org/index.php?page=viewproblem2&cpid=262

'''
1. 如果相邻下一项更大，则我们需要额外的操作次数 ans += a[i] - a[i-1]
2. 如果相邻下一项更小，则可以跟着前面的一起被修改，不消耗次数
'''

import sys
sys.stdin = open('poker.in', 'r')
sys.stdout = open('poker.out', 'w')

n = int(input())
a = [int(input()) for _ in range(n)]
ans = a[0]
for i in range(1,n):
    ans += max(0, a[i] - a[i-1])
print(ans)