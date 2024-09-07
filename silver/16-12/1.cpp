// 二分

// 这道题不能用前缀和，因为位置的范围是10^9，我们无法构建这么大的前缀和
// 换一种处理思路
// 用二分去搜区间两端点在 locations 中的 index
// 假定为 i1 和 i2 那他们的差就是区间草堆数量之和

#include <bits/stdc++.h>
using namespace std;

int main(){
    freopen("haybales.in", "r", stdin);
    freopen("haybales.out", "w", stdout);

    int n,q;
    cin>>n>>q;
    vector<int> hb(n);
    for(int i=0; i<n; i++) cin>>hb[i];
    sort(hb.begin(), hb.end());

    for(int i=0; i<q; i++){
        int left, right;
        cin>>left>>right;
        auto low = lower_bound(hb.begin(), hb.end(), left);         // >= smallest
        auto high = upper_bound(hb.begin(), hb.end(), right);       // > smallest
        cout<<high-low<<endl;
    }
    return 0;
}