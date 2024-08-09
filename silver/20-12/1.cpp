// dfs + greedy

// for each node doubling, we just need to consider the adjcent nodes + 1 ("1" is it need to keep one cow for itself)

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cmath>
using namespace std;

int n, ans = 0;
unordered_map<int, vector<int>> g;
unordered_set<int> already;

void dfs(int x){
    if(already.find(x) != already.end()) return;
    already.insert(x);
    int cow = 1, d = 0, need = g[x].size();     // itself need to keep one
    if(x == 1) need += 1;                       // no parent node
    ans += ceil(log2(need));                    // log() is for e
    for(auto nxt: g[x]) dfs(nxt);
}
int main()
{
    // freopen("1.in", "r", stdin);
    // freopen("1.out", "w", stdout);
    
    cin>>n;
    for(int i=0; i<n-1; i++){
        int a, b;
        cin>>a>>b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    ans = n-1;
    dfs(1);
    cout<<ans<<endl;
    return 0;
}
