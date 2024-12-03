// flood fill + map块统计 + 几何剪枝
// not contained within any other PCL  -- 得确保不包含在其他PCL中 -- 得从大往小 + contain 剪枝

#include<bits/stdc++.h>
using namespace std;

int n,a,b,c,d,ans=0;
char g[21][21];                     // record the colors
int vis[21][21];
unordered_map<char, int> cnt;       // record the number of blocks with different color
vector<vector<int>> PCLs;

void dfs(int x, int y, char color){
    if(x<a || x>c || y<b || y>d || vis[x][y] || g[x][y]!=color) return;
    vis[x][y] = 1;
    dfs(x+1,y,color);
    dfs(x-1,y,color);
    dfs(x,y+1,color);
    dfs(x,y-1,color);
}

bool ok(){
    cnt.clear();
    for(int x=a; x<=c; x++){
        for(int y=b; y<=d; y++){
            if(vis[x][y]) continue;
            dfs(x, y, g[x][y]);
            cnt[g[x][y]]++;                 // record the number
        }
    }

    if(cnt.size() != 2) return false;
    bool cow=false, spot=false;             // the problem requires the spot
    for(auto it: cnt){
        if(it.second == 1) cow = true;      // the original color
        if(it.second > 1) spot = true;      // the spot
    }
    return cow && spot;
}

void resetVis(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++) vis[i][j] = 0;
    }
}

bool is_sub(){         
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
        for(int j=0; j<n; j++) cin>>g[i][j];
    }

    for(a=0; a<n; a++){     // try all rectangle
        for(b=0; b<n; b++){
            for(c=n-1; c>=a; c--){      // from large to small
                for(d=n-1; d>=b; d--){
                    if(is_sub()) continue;   // check whether current image is a part of other PCLs or not
                    resetVis();
                    if(ok()){           // check current rectangle is PCL or not
                        ans++;
                        PCLs.push_back({a,b,c,d});
                    }
                }
            }
        }
    }
    cout<<ans<<endl;
}