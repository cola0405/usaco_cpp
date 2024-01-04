// hash离散化 2D-grid + dfs

// 要注意的是逐个加入cow，每加一次就统计一遍extra
// 只要extra没被真cow顶掉 -- extra 是可以累加的 -- 不然每次都从头开始dfs搜索，10^5肯定超时

#include<bits/stdc++.h>
using namespace std;

int n, extra;

vector<vector<int>> d = {{1,0}, {-1,0}, {0,1}, {0,-1}};
unordered_map<int, unordered_map<int,int>> added;

int comfortable(int x, int y){  // 检测坐标(x,y)的牛是否舒服
    if(added[x][y] == 0) return -1;   // 如果(x,y)都没牛，都不用检查，直接返回-1
    int cnt = 0;
    vector<int> flag(4,0);
    for(int i=0; i<4; i++){     // 往4个方向
        if(added[x+d[i][0]][y+d[i][1]] != 0){
            cnt++;
            flag[i] = 1; 
        }
    }
    if(cnt == 3){   // 如果舒服则返回唯一的空位
        for(int i=0; i<4; i++) if(flag[i] == 0) return i;
    }
    return -1;  // 如果不舒服则返回-1
}

void dfs(int x, int y){     // dfs(x,y)会往(x,y)处放牛 -- 然后dfs看其他牛是否受影响
    if(added[x][y] == 1) return;    // 如果dfs到extra处，则return

    if(added[x][y] == 0){   // 当前处是空白可放牛则放，且extra+1
        extra++;
        added[x][y] = 1;
    }
    int i = comfortable(x,y);   // 除了四周的牛要检查，(x,y)本身也要检查
    if(i != -1) {
        int nextX=x+d[i][0], nextY=y+d[i][1];
        dfs(nextX,nextY);   // 如果当前(x,y)放入的牛舒服，则再往其的空位(nextX,nextY)放牛
    }
    // 向四个方向检查当前牛放入后是否有影响
    for(int j=0; j<4; j++){
        int x1=x+d[j][0], y1=y+d[j][1];
        int i = comfortable(x1,y1);
        if(i != -1) {
            int nextX=x1+d[i][0], nextY=y1+d[i][1];
            dfs(nextX,nextY);   // 如果真的让其他牛变舒服 -- 则dfs(nextX,nextY)
        }
    }
}

int main(){
    // freopen("1.in", "r", stdin);
    // freopen("1.out", "w", stdout);

    cin>>n;
    for(int u=0; u<n; u++){
        int x,y;
        cin>>x>>y;
        if(added[x][y] != 0) extra--;    // (x,y) 不需要extra时-1
        added[x][y] = -1;        // -1 表示真cow -- 此处不再需要extra, 故用标志位-1
        dfs(x,y);
        cout<<extra<<endl;
    }
}