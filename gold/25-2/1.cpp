#include<bits/stdc++.h>
using namespace std;
#define int long long
// 定义节点数量上限
const int MAXN = 200010;
// 节点数量
int n;
// 结构体 node 用于存储每个节点的相关信息
struct node{
    int a; // 表示 f(x) 的值，即从当前节点指向的节点
    int c; // 修改该节点的代价
    int l, r; // 这里 l 和 r 未在后续代码中使用，可能是预留字段
}a[MAXN];
// 重载小于运算符，按修改代价从小到大排序
bool operator < (node x, node y){
    return x.c < y.c;
}
// vis 数组用于标记节点是否已经被访问过
bool vis[MAXN];
// id 数组用于记录节点所在环的编号
int id[MAXN];
// r 数组用于标记节点是否在当前环内
bool r[MAXN];
// rg 向量用于存储当前环上的所有节点
vector<int> rg;
// 邻接表相关数组
int head[MAXN], to[MAXN], nxt[MAXN], tot;
// 添加有向边的函数
inline void add(int u, int v){
    to[++tot] = v; // 记录边的终点
    nxt[tot] = head[u]; // 连接到前一条边
    head[u] = tot; // 更新头指针
}
// dp 数组用于树形 DP
// dp[i][0] 表示不改变节点 i 时，i 的子树的最小总代价
// dp[i][1] 表示改变节点 i 时，i 的子树的最小总代价
int dp[MAXN][2];
// f 数组用于环形 DP
// f[i][0/1][0/1] 表示编号为 i 的节点，选或不选，环上的第一个点选或不选的最小总代价
int f[MAXN][2][2];
// 树形 DP 函数
inline void dfs(int x){
    // 初始化修改节点 x 的代价
    dp[x][1] = a[x].c;
    // 遍历节点 x 的所有子节点
    for(int i = head[x]; i; i = nxt[i]){
        // 如果子节点在当前环内，则跳过
        if(r[to[i]]) continue;
        // 递归处理子节点
        dfs(to[i]);
        // 不改变节点 x 时，加上子节点修改时的最小代价
        dp[x][0] += dp[to[i]][1];
        // 改变节点 x 时，加上子节点修改或不修改时的最小代价
        dp[x][1] += min(dp[to[i]][0], dp[to[i]][1]);
    }
}
signed main() {
    // 读取节点数量
    cin >> n;
    // 读取每个节点的 a 值，并添加有向边
    for(int i = 1; i <= n; i++) {
        cin >> a[i].a;
        add(a[i].a, i);
    }
    // 读取每个节点的修改代价
    for(int i = 1; i <= n; i++) cin >> a[i].c;
    // 初始化最终答案
    int ans = 0;
    // 遍历所有节点，找出所有的环
    for(int i = 1; i <= n; i++){
        // 如果节点已经被访问过，则跳过
        if(vis[i]) continue;
        int x = i;
        // 寻找环 —— 基于题目背景，只要出发了，一定会走到环里！
        while(!vis[x]) {
            vis[x] = 1;
            id[x] = i;
            x = a[x].a;
        }
        // 如果当前环已经处理过，则跳过
        if(id[x] < i) continue;
        // 清空存储当前环节点的向量
        rg.clear();
        // 标记环上的节点
        while(!r[x]) {
            r[x] = 1;
            rg.push_back(x);
            x = a[x].a;
        }
        // 获取环上的最后一个节点
        int l = 0, T = rg[rg.size() - 1];

        // 对于独立的单个节点
        if(rg.size() == 1){
            // 对该节点进行树形 DP
            dfs(T);
            // 因为已经是自环，所以减去修改根的权值
            ans += dp[T][1] - a[T].c;
            continue;
        }

        // 对环上的每个节点进行处理
        for(int j = 0; j < rg.size(); j++){
            int t = rg[j];
            // 对当前节点进行树形 DP，环上的点可能还有子树（每个点只有一个出度，这里的子树是其他点到环上）
            dfs(t);
            if(j > 0){
                // 不选择当前节点，且第一个节点不选
                f[t][0][0] = f[l][1][0] + dp[t][0];
                // 不选择当前节点，且第一个节点选
                f[t][0][1] = f[l][1][1] + dp[t][0];
                // 选择当前节点，且第一个节点不选
                f[t][1][0] = min(f[l][0][0], f[l][1][0]) + dp[t][1];
                // 选择当前节点，且第一个节点选
                f[t][1][1] = min(f[l][0][1], f[l][1][1]) + dp[t][1];
            }
            else{
                // 第一个节点不选，且第一个节点不选
                f[t][0][0] = dp[t][0];
                // 第一个节点不选，且第一个节点选，初始化为一个很大的值
                f[t][0][1] = 1e18;
                // 第一个节点选，且第一个节点选
                f[t][1][1] = dp[t][1];
                // 第一个节点选，且第一个节点不选，初始化为一个很大的值
                f[t][1][0] = 1e18;
            }
            // 更新前一个节点
            l = t;
        }
        // 累加当前环的最小代价到答案中
        ans += min(f[T][0][1], min(f[T][1][1], f[T][1][0]));
    }
    // 输出最终答案
    cout << ans;
    return 0;
}