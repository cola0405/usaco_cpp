// 贪心
// 问题研究的是让花费时间最小
// 因为tp次数有限，所以必然会面临一个问题 -- 到某一节点后是选择tp还是硬等
// 没有明确的判断依据 -- 尝试递归搜索 -- 但这是不可行的 -- 10^4
// 那这道题估计就是贪心了 -- 因为所花费的时间其实就是wait的时间 -- 那就是让wait的时间尽可能小
// 但是从这个角度没有可行的方法，得转化研究对象 -- k次tp
// 要利用有效的tp次数尽可能减少wait的时间 -- 如何让k的价值尽可能大
// 首先，不是简单地距离大就tp，来回穿越是没意义的 -- 得按照某一特定的顺序，比如说从左到右处理
// 不难想到统计相邻节点的距离，但更准确地说应该是相邻tp点距离
// 前k大的gap交给tp，不用wait -- 自然wait就会是最小的

#include<bits/stdc++.h>
using namespace std;

int n,k;
unordered_map<int, int> gap;    // 距离左边最近tp点的距离
priority_queue<int, vector<int>, greater<int>> pq;  // 从小到大排列
vector<int> years;

int main(){
    // freopen("2.in", "r", stdin);
    // freopen("2.out", "w", stdout);

    cin>>n>>k;
    for(int i=0; i<n; i++){
        int year;
        cin>>year;
        years.push_back(year);
        gap[year] = 12-(year%12);
    }
    years.push_back(0); // 0 表示present
    sort(years.begin(), years.end(), greater<int>());   // 从大到小排序

    // 统计相邻tp点之间的gap
    for(int i=0; i<n-1; i++){     // low - high
        pq.push(years[i]-(years[i]%12) - (years[i+1]+gap[years[i+1]]));   
    }
    pq.push(years[n-1]-(years[n-1]%12));    // present 刚好位于tp点，需要特殊处理
    
    k -= 1;  // 第一次肯定要利用跳跃回到最左
    while(pq.size() > k) pq.pop();  // 留下前k大的gap

    unordered_map<int, int> cnt;    // 前k大的可tp的数量统计
    while(!pq.empty()){
        cnt[pq.top()]++;
        pq.pop();
    }

    int ans = 0;
    int cur = years[0] + gap[years[0]];
    for(int i=0; i<=n; i++){
        int tp_gap = cur-(cur%12) - (years[i]+gap[years[i]]);
        if(k>0 && cnt[tp_gap] > 0){     // 当前tp_gap 是前k大，则进行tp
            ans += (cur%12) + gap[years[i]];
            cur = years[i];
            cnt[tp_gap]--;
            k--;
        }
        else{
            ans += cur - years[i];      // 没排到tp的名额 -- 等
            cur = years[i];
        }
    }
    cout<<ans<<endl;
}