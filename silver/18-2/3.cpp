// math函数分析

// 建立二维坐标平面，x轴为传送门的endpoint.y, y轴为d
// 对于每个可用传送有如图所示的函数图像（详看usaco官方解析）
// ---    ----
//    \  / 
//     \/

// 注意其中的三个拐点breakpoint -- 斜率slope发生改变 -- 意味着对应的 d 会改变 —— 函数向下走，即表示d在减小
// 还需要知道，因为 endpoint 每移动一格，对应的 d 也会跟着改变一格 —— 斜率刚好是 -1,0,1
// 那么endpoint从y1到y2, 会有: 总斜率k*(y2-y1) = 总距离d的变化，然后题目就是求总d的最小值
// （这里的总斜率指的是当前段所有斜率(-1,0,1) 叠加起来的结果）

// endpoint 将会出现在所有的拐点breakpoint中
// 注意：在遍历breakpoint的时候，需要对总斜率k、总距离d进行累加（也可以说是实时更新）
// 如果y1到y2刚好是在某段函数的下降区域，那么单纯看slopechg是不对的 —— 它只统计了拐点的总斜率
// 那么在求中间线段的总斜率时，只看相关3拐点的slopechg是不够的，其他在下降的斜率并没有囊括在内
// 除了总斜率k要累计，总距离d进行累加也需要累计
// 原因是y1到y2时，y1时的总距离d已经不再是原始的d了，而应该在每一步遍历的时候进行更新


#include <bits/stdc++.h>
using namespace std;
     
int n;
map<int,int> slopechg;   // slopechg[t] 记录了各拐点的总斜率，且map默认按从小到大排序
int main(){
    freopen("teleport.in", "r", stdin);
    freopen("teleport.out", "w", stdout);

    long long ans = 0;
    cin>>n;
    for(int u=0; u<n; u++){
        int a,b;
        cin>>a>>b;
        ans += abs(a-b);
        if(abs(a) > abs(a-b)) continue;   // 与传送门无关的不需要统计
        slopechg[b] += 2;
        // 只有这四种情况传送门才能发挥作用，记录相关拐点的斜率变化
        if(a<0 && b>0) {slopechg[0]--; slopechg[2*b]--;}    
        if(a<0 && b<a) {slopechg[2*a]--; slopechg[2*b-2*a]--; }
        if(a>0 && b>a) {slopechg[2*a]--; slopechg[2*b-2*a]--;}
        if(a>0 && b<0) {slopechg[0]--; slopechg[2*b]--;}
    }

    int old_y = (*slopechg.begin()).first, slope_sum = 0;    // y=0 则表示没有传送
    long long d = ans;
    for(auto& p: slopechg){
         int cur_y = p.first, breakpoint_slope_cnt = p.second;
         int dy = cur_y - old_y;
         old_y = cur_y;
         d += dy*slope_sum;   // 更新y1处的总距离d
         slope_sum += breakpoint_slope_cnt;  // 更新总斜率

         ans = min(ans,d);
    }
    cout<<ans<<endl;
}