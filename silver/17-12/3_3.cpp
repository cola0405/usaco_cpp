// 频繁地对set进行修改，效率也是低的
// 大小放到50000, 更慢了
// 只过了6个
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
    unordered_set<int> already(50000),abandon(50000);
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