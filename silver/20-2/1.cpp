// quick power

// after k=1, the origin array become a -- {1,5,7,6,2,3,4}
// and the problem is asking when would it be like with K times
// we can treat this problem as quick power to calculate x^k
// quick power time complexity: O(nlogk)
// do the swap: O(mn)
// total: O(mn + nlogk)

// take this example to understand the map:
// a = {1,2,3,4,5,6,7}, b = {1,5,7,6,2,3,4}
// a[0] = a[b[0]]
// so we do know: res[i] = a[b[i]]

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
int n,m,k;
vector<int> a(N+1), origin(N+1);        // a -- k=1, origin -- k=0
vector<int> mul(const vector<int>& x, const vector<int>& y){    // simulation of multiply
    vector<int> res(n+1);
    for(int i=1; i<=n; i++) res[i] = x[y[i]];      
    return res;
}
vector<int> quick_pow(const vector<int>& x, int p){
    if(p == 1) return a;            // origin is p == 0
    auto res = quick_pow(x, p/2);
    if(p&1) return mul(a, mul(res, res));
    return mul(res, res);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("swap.in", "r", stdin);
    freopen("swap.out", "w", stdout);

    cin>>n>>m>>k;
    for(int i=1; i<=n; i++) origin[i] = i, a[i] = i;
    for(int i=0; i<m; i++){
        int l,r; cin>>l>>r;
        reverse(a.begin()+l, a.begin()+r+1);
    }
    auto ans = quick_pow(origin, k);
    for(int i=1; i<=n; i++) cout<<ans[i]<<"\n";
    return 0;
}