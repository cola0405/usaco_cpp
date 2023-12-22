// not contained within any other PCL  -- 得确保不包含在其他PCL中 -- 得从大往小 + contain 剪枝
// flood fill + map块统计 + 几何剪枝

#include<bits/stdc++.h>
using namespace std;

int n,a,b,c,d;
char g[21][21];
int visited[21][21];
unordered_map<char, int> cnt;
vector<vector<int>> PCLs;

void dfs(int x, int y, char color){
    if(x<a || x>c || y<b || y>d || visited[x][y] || g[x][y]!=color) return;
    visited[x][y] = 1;
    dfs(x+1,y,color);
    dfs(x-1,y,color);
    dfs(x,y+1,color);
    dfs(x,y-1,color);
}

bool floodFill(){
    cnt.clear();
    for(int x=a; x<=c; x++){
        for(int y=b; y<=d; y++){
            if(visited[x][y]) continue;
            dfs(x, y, g[x][y]);
            cnt[g[x][y]]++;     // map 统计各种块的数量
        }
    }

    if(cnt.size() != 2) return false;
    bool cow=false, spot=false;     // 通过2个标志位完成复杂条件判断
    for(auto it: cnt){
        if(it.second == 1) cow = true;
        else if(it.second >= 2) spot = true;
    }
    return cow && spot;
}

void resetVisited(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            visited[i][j] = 0;
        }
    }
}

bool contained(){
    for(auto points: PCLs){
        if((a>=points[0] && b>=points[1]) && (c<=points[2] && d<=points[3])) return true;
    }
    return false;
}

int main(){
    freopen("where.in", "r", stdin);
    freopen("where.out", "w", stdout);
    cin>>n;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin>>g[i][j];
        }
    }

    int ans=0, flag=0;
    for(a=0; a<n; a++){     // try all rectangle
        for(b=0; b<n; b++){
            for(c=n-1; c>=a; c--){      // 从大往小找
                for(d=n-1; d>=b; d--){
                    if(contained()) continue;   // 判断是否在大块内
                    resetVisited();
                    if(floodFill()){
                        ans++;
                        PCLs.push_back({a,b,c,d});
                    }
                }
            }
        }
    }
    cout<<ans<<endl;
}