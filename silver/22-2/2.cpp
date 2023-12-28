// combination(40,10)  都费劲
// C(40, 10) = 847,660,528 加上递归 -- 奔10^9去了

#include<bits/stdc++.h>
using namespace std;

int n, cnt1, cnt2;
int xg, yg;
long long totalX=0, totalY=0;
vector<pair<int, int>> ins;
int ans[41];

void combination(vector<int>& inx, int start, int m){    // 搜索所有可行的方案
    if(inx.size() == m){
        long long curX=0, curY=0;
        for(auto i: inx){
            curX += ins[i].first;
            curY += ins[i].second;
        }
        if(curX == xg && curY == yg) cnt1++;
        if(totalX-curX == xg && totalY-curY == yg) cnt2++;  // 阴阳法求解
        return;
    }

    for(int i=start; i<n; i++){
        inx.push_back(i);
        combination(inx, i+1, m);
        inx.pop_back();
    }
}

int main(){
    freopen("2.in", "r", stdin);
    freopen("2.out", "w", stdout);
    
    cin>>n;
    cin>>xg>>yg;

    for(int i=0; i<n; i++){
        int x,y;
        cin>>x>>y;
        ins.push_back(make_pair(x,y));
        totalX += x;
        totalY += y;
    }

    for(int i=0; i<=n/2; i++) {
        cnt1=0, cnt2=0;
        vector<int> v;
        combination(v, 0, i);
        ans[i] = cnt1;
        ans[n-i] = cnt2;
        cout<<i<<endl;
    }

    for(int i=1; i<=n; i++) cout<<ans[i]<<endl;
}