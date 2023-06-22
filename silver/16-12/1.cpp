#include <bits/stdc++.h>
using namespace std;

int main(){
    freopen("haybales.in", "r", stdin);
    freopen("haybales.out", "w", stdout);

    int n,q;
    cin>>n>>q;
    vector<int> hb(n);
    for(int i=0; i<n; i++){
        cin>>hb[i];
    }
    sort(hb.begin(), hb.end());

    // binary search to shrink
    for(int i=0; i<q; i++){
        int left, right;
        cin>>left>>right;
        auto low = lower_bound(hb.begin(), hb.end(), left);
        auto high = upper_bound(hb.begin(), hb.end(), right);
        cout<<high-low<<endl;
    }
    return 0;
}