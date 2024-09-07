// 贪心+二分

#include <bits/stdc++.h>
using namespace std;

bool cmp(pair<int,int>& a, pair<int,int>& b){
    return a.second < b.second;
}

int main(){
    freopen("helpcross.in", "r", stdin);
    freopen("helpcross.out", "w", stdout);
    
    int c,n,x;
    cin>>c>>n;
    multiset<int> chk;
    for(int i=0; i<c; i++) {cin >> x; chk.insert(x);}

    vector<pair<int,int>> cows(n);
    for(int i=0; i<n; i++) cin >> cows[i].first >> cows[i].second;
    sort(cows.begin(), cows.end(), cmp);

    int ans = 0;
    for(auto &[a,b] : cows){
        if(chk.size() == 0) break;
        auto it = chk.lower_bound(a);
        if(it != chk.end() && *it <= b){      // a <= t[i] <= b
            chk.erase(it);
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}