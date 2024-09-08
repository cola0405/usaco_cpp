// 二分lowerbound + 贪心解决最值问题

// 求解：让牛的等待时间尽可能少，然后求其中的最大值
// 首选贪心、二分
// 然后面临一个问题 —— 对于cow[i] 到底是坐当前这辆车，还是下一辆 —— 难有贪心的依据

// 换个思路
// 因为存在单调性，所以我们可以二分去搜答案 
// 对于mid——最长等待时间，我们再用贪心去确认当前 waitting time 是否可行

#include<bits/stdc++.h>
using namespace std;

int n,m,c,ti;
vector<int> t;

// 判断当前等待时长是否可行
bool ok(int wait){              
    int cur = 0;
    for(int i=0; i<m; i++){
        int seat = c;           // 空座位数
        int start = t[cur];     // 当前bus到达时间
        while(cur<n && seat>0 && t[cur]-start <= wait){
            cur++;
            seat--;
        }
    }
    return cur == n;
}

int main(){
    freopen("convention.in", "r", stdin);
    freopen("convention.out", "w", stdout);

    cin>>n>>m>>c;
    t.resize(n);
    for(int i=0; i<n; i++) cin>>t[i];
    sort(t.begin(), t.end());

    int l = 1;
    int r = t.back() - t.front();
    while(l<r){
        int mid = (l+r)/2;      // lower_bound
        if(ok(mid)) r = mid;
        else l = mid+1;
    }
    cout<<l<<endl;
}