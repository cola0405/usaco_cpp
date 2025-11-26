#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
using namespace std;
const int N=51005;
int n,k,b[N],dis[50*N]; // n: 牛的数量, k: 颜色种类, b: 每头牛的颜色, dis: 最短路径数组
bool vis[50*N],S[55][55]; // vis: 访问标记, S: 颜色通信矩阵
int h,t,q[100*N]; // h: 队头, t: 队尾, q: 队列

inline void update(int u,int v,int w){
    if(dis[v])return; // 如果v已经访问过，跳过
    if(w==0){
        q[h--]=v; // 如果边权为0，将v放入队头
        dis[v]=dis[u]; // v的最短路径等于u的最短路径
    }else{
        q[++t]=v; // 如果边权为1，将v放入队尾
        dis[v]=dis[u]+1; // v的最短路径等于u的最短路径加1
    }
}

int main(){
    scanf("%d%d",&n,&k); // 输入牛的数量和颜色种类
    rep(i,1,n)scanf("%d",&b[i]); // 输入每头牛的颜色
    rep(i,1,k)rep(j,1,k){
        char c;
        cin>>c; // 输入颜色通信矩阵
        S[i][j]=c-'0'; // 将字符转换为整数
    }
    dis[1]=1; // 起点的最短路径设为1
    h=50*N,t=50*N+1; // 初始化队头和队尾
    q[t]=1; // 将起点放入队尾
    while(h<t){ // BFS循环
        int x=q[++h]; // 取出队头元素
        if(x<=n){ // 如果x是原图中的节点
            update(x, b[x] * n + x, 0); // 从原图中的x到颜色层b[x]的x
        }else{ // 如果x是分层图中的节点
            int nx=(x-1)/n, ny=(x-1)%n+1; // 找到当前点所在的颜色层和编号
            if(ny>1 && S[nx][b[ny-1]]) update(x, nx * n + ny - 1, 1); // 在同一颜色层内向左移动
            if(ny<n && S[nx][b[ny+1]]) update(x, nx * n + ny + 1, 1); // 在同一颜色层内向右移动
            if(S[nx][b[ny]]) update(x, ny, 0); // 从颜色层的x到原图中的y
        }
    }
    if(dis[n] == 0) printf("-1\n"); // 如果无法到达终点，输出-1
    else printf("%d\n",dis[n]-1); // 输出从1到N的最短路径长度，减1是因为起点的最短路径被设为1
    return 0;
}