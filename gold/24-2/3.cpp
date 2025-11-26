#include<bits/stdc++.h>
#define int long long
using namespace std;
// T 表示测试用例的数量
// n 表示每个测试用例中粒子的数量
// p 数组用于存储每个粒子的初始位置
// s 数组用于存储每个粒子的运动速度
// L 数组用于存储每个粒子的左邻居索引
// R 数组用于存储每个粒子的右邻居索引
// ans 数组用于存储每个粒子消失时的观察次数
int T,n,p[200005],s[200005],L[200005],R[200005],ans[200005];
// 定义结构体 P 用于存储相邻粒子对及其碰撞时间
struct P{
    int l,r,dis;
    // 重载小于运算符，使优先队列成为小顶堆
    bool friend operator<(P a,P b){
        return a.dis>b.dis;
    }
};
// 优先队列，按碰撞时间从小到大存储相邻粒子对
priority_queue<P> q;
// 计算相邻两个粒子 x 和 y 的碰撞时间
int calc(int x,int y){
    // 计算不考虑方向改变时的相遇时间，并向上取整
    // (p[y] - p[x]) 是两个粒子的初始距离
    // (s[x] + s[y]) 是两个粒子的相对速度
    // + s[x] + s[y] - 1 是为了实现向上取整
    // * 2 是考虑粒子每 2 秒改变一次运动方向
    // -(x & 1) 是根据粒子位置的奇偶性进行修正
    return (p[y]-p[x]+s[x]+s[y]-1)/(s[x]+s[y])*2-(x&1);
}
signed main(){
    cin>>T;
    // 循环处理每个测试用例
    while(T--){
        cin>>n;
        // 读取每个粒子的初始位置
        for(int i=1;i<=n;i++)cin>>p[i];
        // 读取每个粒子的运动速度
        for(int i=1;i<=n;i++)cin>>s[i];
        // 初始化链表，每个粒子的左邻居为前一个粒子，右邻居为后一个粒子
        // 并将每个粒子的消失时间初始化为 0
        for(int i=1;i<=n;i++)L[i]=i-1,R[i]=i+1,ans[i]=0;
        // 计算每对相邻粒子的碰撞时间，并将其加入优先队列
        for(int i=1;i<n;i++)q.push({i,i+1,calc(i,i+1)});
        // 当优先队列不为空时，继续处理碰撞
        while(!q.empty()){
            // 取出队列中碰撞时间最小的粒子对
            P u=q.top();
            q.pop();
            // 如果这两个粒子已经消失，则跳过该粒子对
            if(ans[u.l]||ans[u.r])continue;
            // 记录这两个粒子的消失时间
            ans[u.l]=ans[u.r]=u.dis;
            // 如果这两个粒子的左邻居和右邻居都存在
            // 则计算新的相邻粒子对的碰撞时间，并加入优先队列
            if(L[u.l]&&R[u.r]!=n+1)q.push({L[u.l],R[u.r],calc(L[u.l],R[u.r])});
            // 更新链表，删除这两个粒子
            R[L[u.l]]=R[u.r];
            L[R[u.r]]=L[u.l];
        }
        // 输出每个粒子消失时的观察次数
        for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
        // 换行，准备处理下一个测试用例
        puts("");
    }
    return 0;
}