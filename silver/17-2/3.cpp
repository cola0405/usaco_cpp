// 逆向 flood fill
// 题目对 road 的数量没有上限, dfs下去找 distant-pair，压根没办法剪枝
// 可以反向思考，把不需要 road 的 pair 给减去，剩下的就是 distant-pair

#include <bits/stdc++.h>
using namespace std;

int N,K,R;
int ans;
int visited[101][101], isCow[101][101];
vector<pair<int,int>> cows;
unordered_set<string> road;     // 数据太离散才选择用 hash-set

void dfs(int x, int y, int prevX, int prevY){
    if(x<=0 || x>N || y<=0 || y>N || visited[x][y]) return;
    
    // 遇到 road 也不用 dfs 下去
    string s = to_string(prevX)+" "+to_string(prevY) +"-"+ to_string(x)+" "+to_string(y);
    if(road.find(s) != road.end()) return;

    if(isCow[x][y]){
        ans--;  // 减去不需要 road 的，剩下的就都是 distinct-pair 了
    }

    visited[x][y] = 1;
    dfs(x+1,y,x,y);
    dfs(x-1,y,x,y);
    dfs(x,y+1,x,y);
    dfs(x,y-1,x,y);
}

void resetVisited(){
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            visited[i][j] = 0;
        }
    }
}

int main(){
    freopen("countcross.in", "r", stdin);
    freopen("countcross.out", "w", stdout);

    cin>>N>>K>>R;
    ans = K*K;
    for(int i=0; i<R; i++){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        string r1 = to_string(a)+" "+to_string(b) +"-"+ to_string(c)+" "+to_string(d);
        string r2 = to_string(c)+" "+to_string(d) +"-"+ to_string(a)+" "+to_string(b);
        road.insert(r1);
        road.insert(r2);
    }

    for(int i=0; i<K; i++){
        int x,y;
        cin>>x>>y;
        cows.push_back(make_pair(x,y));
        isCow[x][y] = 1;
    }

    for(auto cow: cows){
        int x=cow.first, y=cow.second;
        resetVisited();
        dfs(x, y, x, y);
    }
    cout<<ans/2<<endl;
}