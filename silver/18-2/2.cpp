// dfs + 换/不换
// 250 就是暗示递归了
#include <bits/stdc++.h>
using namespace std;

int n,b,s,d,ans=250;
int f[251];
vector<pair<int,int>> boot;
int visited[251][251];

void dfs(int cur, int j, int cnt){   // 到 cur-tile 时穿的是 boot[j]，当前丢了cnt双
    if(cur >= n-1){
        ans = min(ans, cnt);
        return;
    }
    if(j>=b || visited[cur][j]) return;     // visited 设置得是否有问题
    visited[cur][j] = 1;    // 如果下次到 cur-tile 时穿的仍然是 boot[j]，则不需要继续dfs

    // dfs 尝试往前走 0~d, 然后换/不换靴子
    for(int step=0; step<=boot[j].second; step++){
        if(boot[j].first >= f[cur+step]) {
            dfs(cur+step, j, cnt);  // 不换
        }
    }

    for(int i=j+1; i<b; i++){   // 从 j+1 到 n 中选换一个靴子
        if(boot[i].first >= f[cur]){
            dfs(cur, i, cnt + (i-j)); 
        }
    }
}

int main(){
	freopen("snowboots.in", "r", stdin);
	freopen("snowboots.out", "w", stdout);

    cin>>n>>b;
    for(int i=0; i<n; i++) cin>>f[i];
    for(int i=0; i<b; i++){
        cin>>s>>d;
        boot.push_back(make_pair(s,d));
    }
    dfs(0,0,0);
    cout<<ans<<endl;
}