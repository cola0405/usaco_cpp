// 贪心+二分

#include <bits/stdc++.h>
using namespace std;

bool cmp(vector<int>& a, vector<int>& b){
    return a[1]<b[1];
}

int main(){
    freopen("helpcross.in", "r", stdin);
    freopen("helpcross.out", "w", stdout);
    int c,n;
    cin>>c>>n;
    vector<int> t(c);
    for(int i=0; i<c; i++){
        cin>>t[i];
    }
    sort(t.begin(), t.end());

    vector<vector<int>> cows;
    int a,b;
    for(int i=0; i<n; i++){
        cin>>a>>b;
        cows.push_back({a,b});
    }
    sort(cows.begin(), cows.end(),cmp);

    int ans = 0;
    for(vector<int> pair : cows){
        if(t.size()==0)break;
        int a = pair[0];
        int b = pair[1]
        // 拿a取lower_bound(找最左边被含住的),取到后再和b比较
        int idx = lower_bound(t.begin(), t.end(), a) - t.begin();
        if(t[idx]<=b){
            ans++;
            t.erase(t.begin()+idx);  // 别太害怕
        }
    }
    cout<<ans<<endl;
    return 0;
}