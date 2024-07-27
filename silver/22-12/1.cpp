// tree + topological dfs + 2dfs
// the first dfs is to confirm the hay bales of the substree
// the second dfs is to complete the transportation

// greedy: use every path at most once
// it's a topological problem 

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef long long ll;
using namespace std;

ll n, target;
ll sum = 0;
vector<ll> h(2e5+100);
vector<vector<int>> g(2e5+100);
vector<int> vis1(2e5+100),vis2(2e5+100);
vector<vector<ll>> ans;
vector<ll> sub(2e5+100);    // the number of hay bales from subtree - (target * the number of nodes of subtree)

ll dfs1(int x){     // build sub array
    vis1[x] = 1;
    ll res = h[x] - target;
    for(auto nxt: g[x]){
        if(vis1[nxt] == 0){
            sub[nxt] = dfs1(nxt);
            res += sub[nxt];
        }
    }
    return res;
}

void dfs2(int x){
    // dfs the nodes whose sub[i] > 0 first, gathering the hay
    vis2[x] = 1;
    for(auto nxt: g[x]){
        if(vis2[nxt] == 0 && sub[nxt] > 0){
            dfs2(nxt);
            ans.push_back({nxt, x, sub[nxt]});
        }
    }
    // after gather the extra hay, we can dfs the remain nodes (topological)
    for(auto nxt: g[x]){
        if(vis2[nxt] == 0 && sub[nxt] < 0){
            ans.push_back({x, nxt, -sub[nxt]});     // we need to give it first, because nxt do not have enough hay
            dfs2(nxt);
        }else if(vis2[nxt] == 0 && sub[nxt] == 0) dfs2(nxt);
    }
}

int main()
{
    // freopen("1.in", "r", stdin);
    // freopen("1.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin>>n;
    for(ll i=1; i<=n; i++){
        cin>>h[i];
        sum += h[i];
    }
    for(ll i=0; i<n-1; i++){
        ll a,b;
        cin>>a>>b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    target = sum/n;
    ans.reserve(n);
    dfs1(1);        // n-1 path,so it's a tree, we assume node 1 is the root, we dfs from root
    dfs2(1);
    cout<<ans.size()<<endl;
    for(auto &x: ans){
        cout<<x[0]<<" "<<x[1]<<" "<<x[2]<<'\n';
    }
    return 0;
}
