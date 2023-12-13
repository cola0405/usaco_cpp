// 环中优先级最高的就是答案
// 使用 reach[a][b] 做环检测

#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> wishlist = {{}};
vector<vector<bool>> reach = {{}};

void dfs(int src, int cur){     // reach + dfs找环
    if(reach[src][cur]) return;
    reach[src][cur] = true;
    for(int go: wishlist[cur]){
        dfs(src, go);
    }
}

int main(){
    // freopen("1.in", "r", stdin);
    // freopen("1.out", "w", stdout);
    
    cin>>n;
    for(int i=1; i<=n; i++){
        vector<int> wish(n);
        for(int j=0; j<n; j++) cin>>wish[j];
        while(wish.back() != i) wish.pop_back();    // 保证 wishlist 的有效性
        wishlist.push_back(wish);
        
        reach.push_back(vector<bool>(n+1,false));
    }

    for(int i=1; i<=n; i++) dfs(i,i);   // dfs 构造reach

    for(int a=1; a<=n; a++){
        for(int b : wishlist[a]){   // wishlist[a] 下探
            if(reach[b][a]){        // 如果 b 能回到 a, 那就成环
                cout<<g<<endl;
                break;          // 第一个找到的就是最优的
            }
        }
    }
}