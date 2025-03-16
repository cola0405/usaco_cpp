// 从最终状态往前一个一个拆传送带
// 然后关注可以出去的cell的数量

#include <bits/stdc++.h>
using namespace std;

struct item{
    int x,y;
    char direction;
};

int n,q,out=0;
vector<item> Q;
unordered_map<char, pair<int,int>> d = {{'L',{0,-1}},{'R',{0,1}},{'D',{1,0}},{'U',{-1,0}}};
vector<pair<int,int>> d1 = {{0,-1},{0,1},{1,0},{-1,0}};
vector<vector<char>> grid;
vector<vector<pair<int,int>>> nxt;  // 保存(x,y)位置的next(如果有传送带的话)
vector<vector<int>> flag;       // 可以出去的则标记为 1 否则为 0

void bfs(int x, int y){
    deque<pair<int,int>> q = {{x,y}};
    while(!q.empty()){
        x = q.front().first;
        y = q.front().second;
        q.pop_front();
        if(flag[x][y]) continue;
        flag[x][y] = 1;
        out += 1;
        for(int k=0; k<4; k++){
            int nextx = x + d1[k].first;
            int nexty = y + d1[k].second;
            // 如果(nextx, nexty) 还是unusable，但是(nextx, nexty)可以到(x,y)
            // 或者 (nextx, nexty) 是 '?' 则可以入queue
            if(nextx >= 0 && nextx < n && nexty >= 0 && nexty < n && flag[nextx][nexty] == 0
                && (nxt[nextx][nexty] == make_pair(x,y) || grid[nextx][nexty] == '?')){
                q.push_back({nextx,nexty});
            }
        }
    }

}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x,y,nextx,nexty;
    char direction;
    cin>>n>>q;
    nxt = vector<vector<pair<int,int>>>(n, vector<pair<int,int>>(n));
    flag = vector<vector<int>>(n, vector<int>(n, 0));           // flag = 1 表示可以出去
    grid = vector<vector<char>>(n, vector<char>(n, '?'));       // 表示 cells 的状态 ? 或方向
    for(int i=0;i<q;i++){
        cin>>x>>y>>direction;
        x--; y--;
        grid[x][y] = direction;
        Q.push_back({x,y,direction});
        nextx = x+d[direction].first;
        nexty = y+d[direction].second;
        nxt[x][y] = {nextx,nexty};
    }

    // 检查边界的格子能否出去
    for(int i=0; i<n; i++){
        if(grid[i][0] == '?') bfs(i,0);     // 边界的格子可以出去
        else{                               // 边界的传送带如果方向正确也可以出去
            nextx = i + d[grid[i][0]].first;
            nexty = 0 + d[grid[i][0]].second;
            if(nextx < 0 || nextx >= n || nexty < 0 || nexty >= n) bfs(i,0);
        }
        if(grid[i][n-1] == '?') bfs(i,n-1);
        else{
            nextx = i + d[grid[i][n-1]].first;
            nexty = n-1 + d[grid[i][n-1]].second;
            if(nextx < 0 || nextx >= n || nexty < 0 || nexty >= n) bfs(i,n-1);
        }
        if(grid[0][i] == '?') bfs(0,i);
        else{
            nextx = 0 + d[grid[0][i]].first;
            nexty = i + d[grid[0][i]].second;
            if(nextx < 0 || nextx >= n || nexty < 0 || nexty >= n) bfs(0,i);
        }
        if(grid[n-1][i] == '?') bfs(n-1,i);
        else{
            nextx = n-1 + d[grid[n-1][i]].first;
            nexty = i + d[grid[n-1][i]].second;
            if(nextx < 0 || nextx >= n || nexty < 0 || nexty >= n) bfs(n-1,i);
        }
    }
    vector<int> ans;
    for(int i=q-1; i>=0; i--){      // Q 要反着拆
        x = Q[i].x;
        y = Q[i].y;
        direction = Q[i].direction;
        ans.push_back(n*n - out);  // unusable = 总数 - 能够出去的格子数
        grid[x][y] = '?';
        nxt[x][y] = {x,y};         // 传送带被拆了，更新一下next
        for(int k=0; k<4; k++){
            nextx = x + d1[k].first;
            nexty = y + d1[k].second;
            // 如果(x,y) 与可以出去的格子相连则进行bfs
            if((nextx < 0 || nextx >= n || nexty < 0 || nexty >= n) or flag[nextx][nexty]){
                bfs(x,y);
                break;
            }
        }
    }
    for(int i=q-1; i>=0; i--) cout<<ans[i]<<endl;
    return 0;
}