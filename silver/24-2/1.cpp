// geometry + greedy
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define ll long long

// check if all slopes are valid
bool check(ll b, vector<pair<ll,ll>>& v, vector<ll>& slope){
    vector<ll> max_slopes;
    for(auto& [x,y]: v){
        max_slopes.push_back((y-b)/x);
    }
    sort(max_slopes.begin(), max_slopes.end(), greater<ll>());
    for(int i=0; i<slope.size(); i++){
        if(slope[i] < max_slopes[i]){   // greedy check
            return false;
        }
    }
    return true;
}

ll bis(vector<pair<ll,ll>>& v, vector<ll>& slope){
    ll l=-LONG_LONG_MAX/2, r=LONG_LONG_MAX/2;
    while(l<r){
        ll mid = (l+r)/2;
        if(check(mid, v, slope)) r = mid;
        else l = mid+1;
    }
    return l;
}

void solve(){
    vector<ll> positive_slope, negative_slope;
    vector<pair<ll,ll>> rt,rb,left;
    int n,x1;
    cin>>n>>x1;
    for(int v=0; v<n; v++){
        int y1,x2,y2;
        cin>>y1>>y2>>x2;
        left.push_back({x1,y1});
        left.push_back({x1,y2});
        rt.push_back({x2,y2});

        // symmetric operation, flip the rb to another side of x-axis to make the slope negative
        rb.push_back({x2,-y1});     
    }
    for(int v=0; v<4*n; v++){
        ll k;
        cin>>k;
        if(k>0) positive_slope.push_back(-k);
        else negative_slope.push_back(k);
    }
    
    sort(left.begin(), left.end());     // increasing order
    sort(positive_slope.begin(), positive_slope.end(), greater<ll>());  // descending order
    sort(negative_slope.begin(), negative_slope.end(), greater<ll>());

    // validness check
    if(positive_slope.size() < n || negative_slope.size() < n){
        cout<<-1<<endl;
        return;
    }

    // divide left to ru and rb
    int top_num = negative_slope.size() - n;
    for(int i=0; i<top_num; i++){
        rt.push_back(left[i]);      // the low points should use the negative slope
    }
    for(int i=top_num; i<left.size(); i++){     
        // the high points should use the positive slope
        // but for unified processing, we need to flip it to another side of x-axis with the negative slop also
        rb.push_back({left[i].first, -left[i].second});
    }
    
    ll y_top = bis(rt, negative_slope);
    ll y_bottom = -bis(rb, positive_slope);
    ll ans = y_top - y_bottom;
    if(ans > 0) cout << ans <<endl;
    else cout << -1 << endl;
    
}

int main(){
    // freopen("1.in", "r", stdin);
    // freopen("1.out", "w", stdout);

    int t;
    cin>>t;
    for(int u=0; u<t; u++){
        solve();
    }
    return 0;
}