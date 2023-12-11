// 经典flood fill -- 计算面积、周长

#include <bits/stdc++.h>
using namespace std;

int n;
vector<string> g;
vector<vector<bool>> visited;

int getPerimeter(int i, int j){
    int res = 0;
    vector<vector<int>> v = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    for(int k=0; k<4; k++){
        int x = i+v[k][0];
        int y = j+v[k][1];
        if(x<0 || x>=n || y<0 || y>=n || g[x][y] == '.')res++;
    }
    return res;
}
void dfs(int i, int j, int& area, int& perimeter){      // 多参数时，用引用
    if(i<0 || i>=n || j<0 || j>=n || g[i][j]=='.' || visited[i][j]) return;

    visited[i][j] = 1;
    area++;
    perimeter += getPerimeter(i,j);

    dfs(i+1,j,area,perimeter);
    dfs(i-1,j,area,perimeter);
    dfs(i,j+1,area,perimeter);
    dfs(i,j-1,area,perimeter);
}

int main(){
    freopen("perimeter.in","r",stdin);
    freopen("perimeter.out","w",stdout);

    cin>>n;
    for(int i=0; i<n; i++){
        string line;
        cin>>line;
        g.push_back(line);
        visited.push_back(vector<bool>(n,0));
    }
    
    int ans1=0, ans2=0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(g[i][j]=='#' && !visited[i][j]){
                int area=0, perimeter=0;
                dfs(i,j,area,perimeter);
                if(area > ans1){
                    ans1 = area;
                    ans2 = perimeter;
                }else if(area == ans1){
                    ans2 = min(ans2, perimeter);
                }
            }
        }
    }
    cout<<ans1<<" "<<ans2<<endl;

}