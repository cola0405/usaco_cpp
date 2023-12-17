// first -> second 作一个有向图
// vertex 表示燕麦
// edge 表示牛

// 循环 n 次，每次处理一个 vertex，尽量不 

// (1) 如果 E = V，遍历有 out 的都进行 dfs 即可，得到permutation
// (2) 如果 E > v，找任一节点 dfs 得到 permutation

#include <bits/stdc++.h>
using namespace std;

int n,m;
vector<int> r;
vector<vector<int>> s;
unordered_map<int, vector<int>> components;
unordered_map<int, vector<vector<int>>> edges;
unordered_map<int, unordered_set<int>> g;  // 存储图
vector<vector<int>> fs = {{}};
vector<int> permutation,inDegree;
unordered_set<int> already, cycleAlready;     // 保存已经拿了的cereal
map<vector<int>, int> cow;

int flag;


void findCycle(int cur, int prev){
    int cereal = cow[{prev, cur}];
    if(cycleAlready.find(cur) != cycleAlready.end() && cur!=prev && already.find(cereal) == already.end()) {
        // 成环的关键先选
        permutation.push_back(cereal);
        already.insert(cereal);
        flag = 1;
        return;
    }
    cycleAlready.insert(cur);
    for(auto next: g[cur]){
        findCycle(next, cur);
    }
}

void dfs(int cur){
    if(already.find(cur) != already.end()) return;
    already.insert(cur);
    for(auto next: g[cur]){
        permutation.push_back(cow[{cur, next}]);    // 有些cereal可能没出现过
        dfs(next);
    }
}

int find(int x){
    if(x == r[x]) return x;
    r[x] = find(r[x]);
    return r[x];
}

int main(){
    freopen("3.in", "r", stdin);
    freopen("3.out", "w", stdout);

    cin>>n>>m;
    inDegree.resize(n);     // 这里的内存问题？
    for(int i=0; i<=m; i++) {
        r.push_back(i);
        cow[{i,i}] = i;
        g[i].insert(i);
    }
    for(int i=1; i<=n; i++){
        int f,s;
        cin>>f>>s;
        fs.push_back({f,s});
        inDegree[s]++;  // in-degree count
        r[find(s)] = r[find(f)];    // build disjoint-set
        g[f].insert(s);
        cow[{f,s}] = i;
    }
    
    // build components
    for(int i=1; i<=n; i++){
        components[find(i)].push_back(i);
        edges[find(fs[i][0])].push_back(fs[i]);
    }

    for(int i=1; i<=m; i++){    // 遍历所有cereal
        flag = 0;
        findCycle(i, -1);
        if(flag){
            dfs(find(i));
        }else{
            dfs(i);
        }

        // if(g[i].find(find(i)) != g[i].end()){       // 有向图的构成假环，就足够了
        //     permutation.push_back(cow[{i, find(i)}]);
        //     already.insert(i);
        //     dfs(find(i));  // 摘完extra后，从root开始dfs
        // }else{
        //     dfs(i);     // 没有环，那就从当前dfs
        // }
    }

    int ans = 0;
    for(auto comp: components){     // iterate through the components
        int root = comp.first;
        vector<int> vertices = comp.second;
        int vtxCount = vertices.size();
        int edgeCount = edges[root].size();

        if(edgeCount > vtxCount){
            ans += max(0, edgeCount - vtxCount);
        }
    }

    cout<<ans<<endl;
    for(auto k: permutation) cout<<k<<endl;
    cout<<endl;
    for(auto it: cow) cout<<it.first[0]<<" "<<it.first[1]<<endl;
}
