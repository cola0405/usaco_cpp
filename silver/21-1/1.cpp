// union-find + graph

// after all k operation, some cows will stay in different places or stay in same place
// if the cow stay in the same place, which means the cow will only visit the places of the loop
// if not, the visted place should also include other cows' places in the same union block

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
int n,k;
vector<int> cow(N+1);
vector<unordered_set<int>> s;
vector<int> root(N+1, 0);
vector<pair<int,int>> op;

int find(int x){
    if(x == root[x]) return x;
    root[x] = find(root[x]);
    return root[x];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("1.in", "r", stdin);

    cin>>n>>k;
    s.resize(n+1);
    for(int i=1; i<=n; i++){        // init
        cow[i] = i;     
        root[i] = i;
        s[i].insert(i);             // answer >= 1
    }
    for(int i=0; i<k; i++){
        int a,b;
        cin>>a>>b;
        swap(cow[a], cow[b]);
        op.push_back(make_pair(a,b));
    }

    // build union-find array
    for(int i=1; i<=n; i++) root[i] = find(cow[i]);     // check the end situation

    // reset cow[]
    for(int i=1; i<=n; i++) cow[i] = i;

    // count the places for each block based on the union-find
    for(auto &[a,b] : op){
        s[find(cow[a])].insert(b);
        s[find(cow[b])].insert(a);
        swap(cow[a], cow[b]);
    }
    for(int i=1; i<=n; i++) cout<<s[find(i)].size()<<"\n";
    return 0;
}