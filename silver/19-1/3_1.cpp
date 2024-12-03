// 模仿 lifeguard
// 问题出在多个挨着的山脚 —— 顺序以及对应会出问题
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("mountains.in","r",stdin);
    freopen("mountains.out","w",stdout);
    
    unordered_set<int> left, skip;
    vector<pair<int,int>> v, q;
    int n,a,b,ans, first=0;
    cin>>n;
    
    for(int i=0;i<n;i++){
        cin>>a>>b;
        v.push_back({a-b, i});
        v.push_back({a+b, i});
        q.push_back({a-b, i});
    }
    sort(v.begin(), v.end());
    sort(q.begin(), q.end());
    ans = n;
    for(auto &[pos, id]: v){
        if(left.find(id) != left.end()){    // rigth end of the interval
            if(id != q[first].second) ans--;
            left.erase(id);
            skip.insert(id);
            while(first < q.size() && skip.find(q[first].second) != skip.end()){
                first++;
            }
        }
        else {
            left.insert(id);
        }
    }
    cout<<ans<<endl;
    return 0;
}