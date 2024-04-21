#include<bits/stdc++.h>
using namespace std;

int n;
int potions[100001];
unordered_map<int, vector<int>> g;
unordered_set<int> already;
vector<vector<int>> paths(100001);

void dfs(int cur, vector<int> path){
    if(g[cur].empty()) return;

    if(already.find(cur) != already.end()) return;
    paths[cur] = path;
    for(auto nxt: g[cur]){
        path.push_back(nxt);
        dfs(nxt, path);
        path.pop_back();
    }
}

int main(){
    freopen("2.in", "r", stdin);
    freopen("2.out", "w", stdout);

    cin>>n;
    for(int i=0; i<n; i++) cin>>potions[i];
    for(int i=0; i<n; i++){
        int src,dst;
        cin>>src>>dst;
        g[src].push_back(dst);
    }

    dfs();

    for(int i=0; i<n; i++){
        int dst = potions[i];

    }
    

}