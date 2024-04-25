// graph + O(n)dfs + leaf nodes + hidden in_deg

// to achieve the first goal, the number of leaf nodes is actually the number of traversals
// use dfs to calculate the maxinum number of potions that can be farmed at each node
// ans is actually the potions gained from each branch of the tree
// each branch = min(visited times, potions from sub-branch + potions generated at the node)
#include<bits/stdc++.h>
using namespace std;

int n, ans=0;
int p[100001];  // record the appearance of potions
unordered_map<int, vector<int>> g;
vector<int> leaf_cnt;         // the number of leaf nodes of node i (also the number of times node i is visited)
vector<int> generated_potion; // the number of potions generated at node i

int dfs1(int node, int pre){    
    int cnt = 0;
    if(g[node].size() == 1 && node != 1) cnt++;     // root is not leaf
    for(auto nxt: g[node]){
        if(nxt == pre) continue;
        cnt += dfs1(nxt, node);
    }
    return leaf_cnt[node] = cnt;
}

int dfs2(int node, int pre){
    int cnt = 0;
    for(auto nxt: g[node]){
        if(nxt == pre) continue;
        cnt += dfs2(nxt, node);
    }
    // the leaf_cnt[node] is actually the number of times node i is visited
    // the number of farmed potions must less than the visited time
    return min(leaf_cnt[node], cnt + generated_potion[node]);
}

int main(){
    // freopen("2.in", "r", stdin);
    // freopen("2.out", "w", stdout);

    int a,b;
    cin>>n;
    leaf_cnt.resize(n+1);
    generated_potion.resize(n+1);
    for(int i=0; i<n; i++) cin>>p[i];
    for(int i=0; i<n-1; i++){
        cin>>a>>b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int k = 0;      // the number of leaf nodes
    for(int i=1; i<=n; i++){
        if(g[i].size() == 1) {      // don't need the in_deg here (hidden in_deg)
            leaf_cnt[i]++;
            k++;
        }
    }
    k--;    // root is not leaf node
    // the first k generated potions are available
    for(int i=0; i<k; i++) generated_potion[p[i]]++;
    dfs1(1,-1);        // recursively calculate the number of leaf nodes
    cout<<dfs2(1,-1)<<endl;      // recursively calculate the number of potions
}