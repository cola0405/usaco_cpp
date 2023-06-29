// 暴力过7/10
// 没过的因为内存爆了。。 大数组复制太消耗空间了
#include <bits/stdc++.h>
using namespace std;

int main(){
    freopen("shuffle.in", "r", stdin);
    freopen("shuffle.out", "w", stdout);

    int n;
    cin>>n;
    vector<int> order(n+1);
    vector<int> cows(n+1,1);
    for(int i=1; i<=n; i++){
        cin>>order[i];
    }
    set<vector<int>> already;
    vector<int> count(n+1,1);
    while(already.find(cows) == already.end()){
        already.insert(cows);
        // do shuffle
        for(int i=1; i<=n; i++){
            if(cows[i]>0){
                cows[order[i]] += 1;
            }
            cows[i] = max(cows[i]-1, 0);
        }
        for(int i=1; i<=n; i++){
            if(cows[i] == 0){
                count[i] = 0;
            }
        }
    }
    int ans=0;
    for(int i=1; i<=n; i++){
        if(count[i]==1)ans++;
    }
    cout<<ans<<endl;
    return 0;
}