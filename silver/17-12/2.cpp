// set不是万能的
// 在频繁修改set的情境下，可以使用visit表，达到快速check的目的
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
    vector<int> abandon(100001);
    for(int i=1; i<=n; i++){
        int cur = i;
        if(abandon[cur] == 1)continue; // 每个位置只有一个"出"，所以剪枝
        while(true){
            if(abandon[cur] == 2){
                // deal with the cycle
                ans++;
                int end = cur;
                abandon[end] = 1;
                cur = next[cur];
                while(cur != end && abandon[cur]!=1){
                    ans++;
                    abandon[cur] = 1;
                    cur = next[cur];
                }
            }
            if(abandon[cur] == 1 || abandon[cur] == 2){
                // abandon head chain
                int end = cur;
                cur = i;
                while(cur != end){
                    abandon[cur] = 1;
                    cur = next[cur];
                }
                break;
            }
            // traveling mark
            abandon[cur] = 2;
            cur = next[cur];
        }
    }
    cout<<ans<<endl;
    return 0;
}