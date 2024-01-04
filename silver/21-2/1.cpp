// 不超时了

#include<bits/stdc++.h>
using namespace std;

int n, pre;
int g[1001][1001];
vector<vector<int>> d = {{1,0}, {-1,0}, {0,1}, {0,-1}};
unordered_map<int, unordered_map<int,int>> added, record;

int comfortable(int x, int y){
    int cnt = 0;
    vector<int> flag(4,0);
    for(int i=0; i<4; i++){
        int x1=x+d[i][0], y1=y+d[i][1];
        if((x1>=0 && x1<=1000 && y1>=0 && y1<=1000 && g[x1][y1]) || record[x1][y1] != 0) {
            cnt++;
            flag[i] = 1; 
        }
    }
    if(cnt == 3){
        for(int i=0; i<4; i++){
            if(flag[i] == 0) return i;
        }
    }
    return -1;
}

void dfs(int x, int y){     // 只有填才会进入到dfs中
    // if(x>=0 && x<=1000 && y>=0 && y<=1000 && g[x][y]==0 && added[x][y] == 0) return ;    // 界内空位
    // else if((x<0 || x>1000 || y<0 || y>1000) && added[x][y] == 0) return ; // 界外空位
    if(added[x][y] == 1) return;

    added[x][y] = 1;
    if(record[x][y] == 0){
        pre++;
        record[x][y] = 1;
    }
    for(int j=0; j<4; j++){
        int x1=x+d[j][0], y1=y+d[j][1];
        int i = comfortable(x1,y1);
        if(i != -1) {
            int nextX=x1+d[i][0], nextY=y1+d[i][1];
            dfs(nextX,nextY);
            // record[nextX][nextY] = 1;
        }
    }

    added[x][y] = 0;
    // return res;
}

int main(){
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);

    cin>>n;
    for(int u=0; u<n; u++){
        int x,y;
        cin>>x>>y;
        g[x][y] = 1;
        if(record[x][y] != 0){
            pre--;
        }
        record[x][y] = -1;
        dfs(x,y);
        
        // cout<<pre + dfs(x,y)<<endl;
        cout<<pre<<endl;
    }
}