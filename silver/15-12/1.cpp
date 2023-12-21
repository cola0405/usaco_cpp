// 离散 flood fill + flood 检查

#include<bits/stdc++.h>
using namespace std;

int n,m;
vector<pair<int,int>> sw[101][101];
int room[101][101], visited[101][101];
vector<pair<int, int>> d = {{1,0}, {-1,0}, {0,1}, {0,-1}};

// dfs is better for flood fill 
void dfs(int x, int y){
    if(x<=0 || x>n || y<=0 || y>n || room[x][y] == 0 || visited[x][y]) return;
    visited[x][y] = 1;
    for(auto r: sw[x][y]){
        int a=r.first, b=r.second;
        room[a][b] = 1;
        for(auto it: d){                            // room 用来统计亮灯数量但无法检查 flood
            if(visited[a+it.first][b+it.second]){   // visited 可以用来检查 flood，另一方面也防止dfs回流
                dfs(a, b);  // 离散的dfs
            }
        }
    }

    dfs(x+1,y);
    dfs(x-1,y);
    dfs(x,y+1);
    dfs(x,y-1);
}

int main(){
    freopen("lightson.in", "r", stdin);
    freopen("lightson.out", "w", stdout);

    cin>>n>>m;
    for(int i=0; i<m; i++){
        int x,y,a,b;
        cin>>x>>y>>a>>b;
        sw[x][y].push_back(make_pair(a,b));
    }

    room[1][1] = 1;
    dfs(1,1);

    int ans = 0;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(room[i][j]) ans++;
        }
    }
    cout<<ans<<endl;
}