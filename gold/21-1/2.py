from collections import deque

# 定义一个常量 N，用于数组大小，确保有足够空间存储节点信息
N = 51005

# 定义更新函数，用于更新节点的距离信息并将节点加入队列
def update(u, v, w):
    global dis, q
    # 如果目标节点 v 已经被访问过（dis[v] 不为 0），则不做处理直接返回
    if dis[v]:
        return
    # 如果边权 w 为 0，将目标节点 v 插入到队列头部，并且目标节点的距离等于当前节点的距离
    if w == 0:
        q.appendleft(v)
        dis[v] = dis[u]
    # 如果边权 w 不为 0，将目标节点 v 插入到队列尾部，并且目标节点的距离等于当前节点的距离加 1
    else:
        q.append(v)
        dis[v] = dis[u] + 1

# 主函数部分，开始处理输入和执行 BFS 算法
n, k = map(int, input().split())
# 读取每头奶牛的颜色，下标从 1 开始，前面补 0 是为了方便从 1 开始索引
b = [0] + list(map(int, input().split()))
# 初始化颜色邻接矩阵 S，用于表示不同颜色之间是否可以传递消息
S = [[False] * (k + 1) for _ in range(k + 1)]
# 初始化距离数组 dis，用于记录每个节点到起点的最短距离
dis = [0] * (50 * N)
# 初始化双端队列 q，用于 BFS 算法
q = deque()

# 读取矩阵 S 的每一行
for i in range(1, k + 1):
    row = input().strip()
    # 读取矩阵 S 的每一列元素，并将其转换为布尔值存储在 S 矩阵中
    for j in range(1, k + 1):
        S[i][j] = bool(int(row[j - 1]))

# 将起点的距离设为 1
dis[1] = 1
# 将起点加入队列
q.append(1)

# 开始 BFS 遍历
while q:
    # 从队列中取出一个节点
    x = q.popleft()
    # 如果 x 是原图中的节点（x <= n）
    if x <= n:
        # 调用 update 函数将其连接到第 b[x] 层的 x 号节点，边权为 0
        update(x, b[x] * n + x, 0)
    # 如果 x 是分层图中的节点（x > n）
    else:
        # 计算 x 所在的层
        nx = (x - 1) // n
        # 计算 x 在该层的位置
        ny = (x - 1) % n + 1
        # 如果当前位置不在该层的第一个位置
        if ny > 1:
            # 调用 update 函数将 x - 1 加入队列，边权为 1
            update(x, x - 1, 1)
        # 如果当前位置不在该层的最后一个位置
        if ny < n:
            # 调用 update 函数将 x + 1 加入队列，边权为 1
            update(x, x + 1, 1)
        # 如果当前层的颜色可以向第 b[ny] 颜色的节点传递消息
        if S[nx][b[ny]]:
            # 调用 update 函数将 ny 加入队列，边权为 0
            update(x, ny, 0)

# 输出从节点 1 到节点 N 的最短距离，由于初始距离设为 1，所以要减 1
print(dis[n] - 1)