// 问题转换
// 说白了就是让A+B尽可能小，然后求A+B的最大值
// sort+贪心+双指针
// 又因为数据范围，没办法用线性表，得用hash表

#include <bits/stdc++.h>
using namespace std;

int main(){
    freopen("pairup.in", "r", stdin);
    freopen("pairup.out", "w", stdout);

    int n;
    cin>>n;
    unordered_map<int,int> count;
    for(int i=0; i<n; i++){
        int x,y;
        cin>>x>>y;
        count[y] += x;
    }
    vector<int> output;
    for(auto item: count){
        output.push_back(item.first);
    }
    sort(output.begin(), output.end());

    int ans=0;
    int i=0, j=output.size()-1;
    while(i<=j){
        if(count[output[i]]<=0)i++;
        if(count[output[j]]<=0)j--;
        ans = max(output[i]+output[j], ans);
        int cost = min(count[output[i]], count[output[j]]);
        count[output[i]] -= cost;
        count[output[j]] -= cost;
    }
    cout<<ans<<endl;

    return 0;
}