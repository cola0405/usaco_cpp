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
vector<vector<int>> st;
unordered_map<int, vector<int>> components;
unordered_map<int, int> edges;
unordered_map<int, vector<int>> g;  // 存储图
vector<vector<int>> fs = {{}};
vector<int> permu,inDegree;
unordered_set<int> already;    // 被吃掉的cereal
map<vector<int>, vector<int>> cow;
vector<int> visited;

void check(int src, int dst){
    int x = cow[{src,dst}].back();
    if(already.find(src) == already.end()){
        permu.push_back(x);
        already.insert(x);
        cow[{src,dst}].pop_back();
    }else if(already.find(dst) == already.end()){
        permu.push_back(x);
        already.insert(x);
        cow[{src,dst}].pop_back();
    }else if (already.find(x) == already.end()){
        permu.push_back(x);     // 没燕麦吃，但要放进permutation
        already.insert(x);
        cow[{src,dst}].pop_back();
    }
}

void dfs(int cur){     // 遍历往 permutation 放就行
    if(visited[cur]) return;
    visited[cur] = 1;
    for(auto dst: g[cur]){
        if(g.find(dst) == g.end()){
            st.push_back({cur, dst});   // 之后如果cur已经入already，则可以直接选dst
            continue;
        }
        check(cur, dst);
        inDegree[dst]--;
        dfs(dst);
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
    inDegree.resize(n+1);
    visited.resize(n+1);
    for(int i=0; i<=m; i++) r.push_back(i);
    for(int i=1; i<=n; i++){
        int f,s;
        cin>>f>>s;
        vector<int> line = {f,s};
        fs.push_back(line);
        cow[line].push_back(i);      // line 可能重复！    
        inDegree[s]++;  // in-degree count
        r[find(s)] = r[find(f)];    // build disjoint-set
        g[f].push_back(s);
    }
    
    // build components
    for(int i=1; i<=n; i++){
        components[find(i)].push_back(i);
        edges[find(fs[i][0])]++;
    }

    int ans = 0;
    for(auto comp: components){     // iterate through the components
        int root = comp.first;
        vector<int>& vertices = comp.second;
        int vtxCount = vertices.size();
        int edgeCount = edges[root];
        st.clear();

        if(edgeCount < vtxCount){   // 燕麦很充裕，随便给都行
            for(int vertex: vertices) dfs(vertex);
        }else if(edgeCount == vtxCount){
            for(int vertex: vertices) dfs(vertex);
        }else{
            ans += max(0, edgeCount - vtxCount);
            for(int vertex: vertices) dfs(vertex);
        }

        for(auto item: st){
            int src = item[0], dst = item[1];
            check(src, dst);
        }

    }
    cout<<ans<<endl;
    for(auto x: permu) {
        cout<<x<<endl;
    }
    return 0;
}