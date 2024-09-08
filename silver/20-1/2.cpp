#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k,m;

bool ok(ll x){
    int day = 0;
    ll g = 0;
    while(g < n && day < k){
        ll y = (n-g)/x;
        if(y <= m) {
            day += ceil(float(n-g)/m);  // set it to float
            g=n; break;
        }      
        g += y;
        day++;
    }
    return g >= n;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("loan.in", "r", stdin);
    // freopen("loan.out", "w", stdout);

    cin>>n>>k>>m;
    ll low=0, high=n;
    while(low < high){
        ll mid = (low+high+1)/2;
        if(ok(mid)) low = mid;
        else high = mid-1;
    }
    cout<<low<<endl;
    return 0;
}