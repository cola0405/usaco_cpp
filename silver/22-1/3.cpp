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
unordered_map<int, vector<int>> g;  // 存储图
vector<vector<int>> fs = {{}};
vector<int> permutation,inDegree;
unordered_set<int> already;

void dfs(int cur){     // 遍历往 permutation 放就行
    if(already.find(cur) != already.end()) return;
    for(auto dst: g[cur]){
        if(g.find(dst) == g.end()){
            s.push_back({cur, dst});   // 之后如果cur已经入already，则可以直接选dst
            continue;
        }
        if(already.find(cur) == already.end()){
            permutation.push_back(cur);
        }
        already.insert(cur);
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
    inDegree.resize(n);
    for(int i=0; i<=n; i++) r.push_back(i);
    for(int i=0; i<n; i++){
        int f,s;
        cin>>f>>s;
        fs.push_back({f,s});
        inDegree[s]++;  // in-degree count
        r[find(s)] = r[find(f)];    // build disjoint-set
        g[f].push_back(s);
    }
    
    // build components
    for(int i=1; i<=n; i++){
        components[find(i)].push_back(i);
        edges[find(fs[i][0])].push_back(fs[i]);
    }

    int ans = 0;
    for(auto comp: components){     // iterate through the components
        int root = comp.first;
        vector<int> vertices = comp.second;
        int vtxCount = vertices.size();
        int edgeCount = edges[root].size();

        if(edgeCount < vtxCount){   // 燕麦很充裕，随便给都行
            // permutation.insert(permutation.end(), vertices.begin(), vertices.end());
            for(int vertex: vertices){
                 if(inDegree[vertex] <= 0) dfs(vertex);
            }
        }else if(edgeCount == vtxCount){
            for(int vertex: vertices){
                 if(inDegree[vertex] <= 0) dfs(vertex);
            }
        }else{
            ans += max(0, edgeCount - vtxCount);
            for(int vertex: vertices){
                if(inDegree[vertex] <= 0) dfs(vertex);
            }
        }

        for(auto item: s){
            int src = item[0], dst = item[1];
            if(already.find(src) == already.end()){
                permutation.push_back(src);
                already.insert(src);
            }else if(already.find(dst) == already.end()){
                permutation.push_back(dst);
                already.insert(dst);
            }
        }

    }
    cout<<ans<<endl;
    for(auto cow: permutation) cout<<cow<<endl;
}