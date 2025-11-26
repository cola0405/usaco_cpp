#include<iostream>
#include<vector>
using namespace std;
// n 表示节点数量，m 表示边的数量
int n,m,fa[200005],sz[200005];
// sum 用于记录当前图中能够相互到达的节点对的数量
// ans 数组用于存储每个时间步之前能够相互到达的节点对的数量
long long sum,ans[200005];
// g 是邻接表，g[i] 存储与节点 i 相邻的节点
vector<int> g[200005];
// s 数组用于记录每个节点的操作类型（0 或 1）
bool s[200005];

// 并查集的查找操作，用于查找节点 u 所在连通分量的根节点，并进行路径压缩
int get(int u){
    return (u==fa[u])?u:(fa[u]=get(fa[u]));
}

// 并查集的合并操作，用于合并节点 u 和 v 所在的连通分量
void c(int u,int v)
{
    // 如果 u 和 v 不在同一个连通分量中
    if(get(u)!=get(v))
    {
        // 获取 u 和 v 所在连通分量的根节点
        u=fa[u],v=fa[v];
        // 将 u 所在连通分量合并到 v 所在连通分量
        fa[u]=v;
        // 计算合并后新增的可达节点对数量，并累加到 sum 中
        sum+=(1ll*sz[u]*sz[v]);
        // 更新 v 所在连通分量的大小
        sz[v]+=sz[u]; 
    }
}

// 向连通分量中添加一个新节点
void add(int u)
{
    // 获取节点 u 所在连通分量的根节点
    u=get(u);
    // 新节点与原连通分量中节点的可达节点对数量累加到 sum 中
    sum+=sz[u];
    // 增加连通分量的大小
    sz[u]++;
}

int main()
{
    // 读取节点数量 n 和边的数量 m
    cin>>n>>m;
    char ch;
    // 初始化并查集，每个节点的父节点为自身，连通分量大小为 0
    for(int i=1;i<=n;i++)
        fa[i]=i,sz[i]=0;
    // 读取二进制字符串 s，记录每个节点的操作类型
    for(int i=1;i<=n;i++)
    {
        cin>>ch;
        s[i]=(ch=='1');
    }
    // 读取每条边，并添加到邻接表中
    for(int i=1,u,v;i<=m;i++)
    {
        cin>>u>>v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
        // 如果两个节点的操作类型都为 1，则合并它们所在的连通分量
        if(s[u] && s[v])
            c(u,v);
    }
    // 逆向处理，从最后一个时间步开始，逐步添加节点和边
    for(int i=n;i>=1;i--)
    {
        // 遍历节点 i 的相邻节点
        for(int j:g[i])
        {
            // 如果相邻节点 j 的编号大于 i 或者 j 的操作类型为 1，则合并节点 i 和 j 所在的连通分量
            if(j>i || s[j]==1)
                c(i,j);
        }
        // 向连通分量中添加节点 i
        add(i);
        // 记录当前时间步之前能够相互到达的节点对的数量
        ans[i]=sum;
    }
    // 按顺序输出每个时间步之前能够相互到达的节点对的数量
    for(int i=1;i<=n;i++)
        cout<<ans[i]<<endl;
    return 0;
}