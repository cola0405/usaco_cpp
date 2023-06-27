// 说白了拿一个长度为k的窗口直接滑就行。。。
// 前缀和帮助统计区间内坏信号灯的数量，找最小值
// 区间问题 - 前缀和

#include <bits/stdc++.h>
using namespace std;

int main(){
    freopen("maxcross.in", "r", stdin);
    freopen("maxcross.out", "w", stdout);
    
    int n,k,b;
    cin>>n>>k>>b;
    vector<int> broken(n);
    for(int i=0; i<b; i++){
        int id;
        cin>>id;
        broken[id-1] = 1;
    }
    vector<int> count(n+1);
    for(int i=1; i<=n; i++){
        count[i] = count[i-1];
        if(broken[i]) count[i]++;
    }
    
    int ans = INT_MAX;
    for(int i=1; i<=n-k+1; i++){
        int broken_count = count[i+k-1]-count[i-1];
        ans = min(broken_count, ans);
    }
    cout<<ans<<endl;
    return 0;
}