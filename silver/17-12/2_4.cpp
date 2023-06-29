// 频繁地对set进行修改，效率也是低的
// 修改负载因子到0.9，数据量大时，可以快几倍
// 但是第八个测试用例还是没有过
#include <bits/stdc++.h>
using namespace std;

int main(){
    freopen("shuffle.in", "r", stdin);
    freopen("shuffle.out", "w", stdout);

    int n;
    cin>>n;
    vector<int> next(n+1);
    for(int i=1; i<=n; i++){
        cin>>next[i];
    }
    
    int ans = 0;
    unordered_set<int> already,abandon;
    already.max_load_factor(0.9);
    abandon.max_load_factor(0.9);
    for(int i=1; i<=n; i++){
        int cur = i;
        while(true){
            if(abandon.find(cur)!=abandon.end()){
                abandon.insert(already.begin(), already.end());
                already.clear();
                break;
            }
            if(already.find(cur)!=already.end()){
                abandon.insert(already.begin(), already.end());
                ans++;
                int end = cur;
                cur = next[cur];
                while(cur != end){
                    ans++;
                    cur = next[cur];
                }
                already.clear();
                break;
            }
            already.insert(cur);
            cur = next[cur];
        }
    }
    cout<<ans<<endl;
    return 0;
}