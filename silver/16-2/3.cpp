// dfs 模拟
// 剪枝不一定要找if条件，3参剪枝也是常见的一种方式

#include<bits/stdc++.h>
using namespace std;

int X,Y,K,M;
int ans = 200;
int visited[101][101][101];

void dfs(int x, int y, int k){
    if(ans == 0 || visited[x][y][k]) return;
    if(k==0){
        ans = min(ans, abs(x+y-M));
        return;
    }
    
    visited[x][y][k] = 1;
    ans = min(ans, abs(x+y-M));

    dfs(X, y, k-1);
    dfs(x, Y, k-1);
    dfs(0, y, k-1);
    dfs(x, 0, k-1);
    dfs(max(0,x-(Y-y)), min(x+y,Y), k-1);
    dfs(min(x+y,X), max(0,y-(X-x)), k-1);
}

int main(){
    freopen("pails.in", "r", stdin);
    freopen("pails.out", "w", stdout);

    cin>>X>>Y>>K>>M;
    dfs(0,0,K);
    cout<<ans<<endl;
}