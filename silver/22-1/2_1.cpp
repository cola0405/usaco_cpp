// 这个对于数据规模小没有问题 -- 一步步累加
// 但是这里是10^5 O(n^2) 超时 -- 比mid小的无法统计，但是又得往下走 -- 这就是超时的原因

#include<bits/stdc++.h>
using namespace std;

int n;
int h[300001];
int main(){
    // freopen("2.in", "r", stdin);
    // freopen("2.out","w", stdout);

    cin>>n;
    for(int u=0; u<n; u++) cin>>h[u];
    long long ans = 0;    // [i] 和 [i+1]
    for(int i=0; i<n-1; i++){
        int mid = 0;
        for(int j=i+1; j<n; j++){
            if(h[j] > mid) ans += j-i+1;    // 比mid小的无法统计，但是又得往下走 -- 这就是超时的原因
            if(h[j] > h[i]) break;
            mid = max(mid, h[j]);
        }
    }
    cout<<ans<<endl;
}