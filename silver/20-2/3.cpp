// graph + dfs sim

// thinking about greedy, but not working
// but aparently, the N = 2500 is telling us we can use O(n^2), brute force dfs
// try every room as the start place and check the validation

// for dfs, always dealing with the leaf nodes first, then the parent nodes
// we can make sure fixing the son nodes
// then just fix them and check the parent node in the end

#include <bits/stdc++.h>
using namespace std;

const int N = 2500;
int n;
vector<int> c(N+1), origin(N+1);
unordered_map<int, vector<int>> g;

void dfs(int x, int pre){
    for(auto nxt: g[x]){ 
        if(nxt == pre) continue;
        dfs(nxt, x);    // dealing with leaf first
        c[x] = (c[x] + (12 - c[nxt])%12) % 12;      // c[x] it will only be affected by all c[nxt]
        c[nxt] = 0;     // we can make sure fixing the sub-node
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("clocktree.in", "r", stdin);
    freopen("clocktree.out", "w", stdout);

    cin>>n;
    for(int i=1;i<=n;i++) {cin>>c[i]; origin[i] = c[i];}
    for(int i=0;i<n-1;i++){
        int a,b; cin>>a>>b;
        g[a].push_back(b); g[b].push_back(a);
    }
    int ans = 0;
    for(int i=1;i<=n;i++){
        dfs(i, -1);     // by defualt, FJ will always go back to start place
        // c[i] == 0 means when FJ back to start place, all clock already set to 12
        // c[i] == 1 means FJ already finish the setting, but still go back to start place, making c[i]+1 
        if(c[i] == 0 || c[i] == 1) ans += 1;        
        for(int j=1;j<=n;j++) c[j] = origin[j];     // reset array c
    }
    cout<<ans<<endl;
    return 0;
}