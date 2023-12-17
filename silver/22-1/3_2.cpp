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
// unordered_map<int, vector<vector<int>>> edges;
// unordered_map<int, unordered_set<int>> g;  // 存储图
vector<vector<int>> fs = {{}};
vector<int> permutation,inDegree;
unordered_set<int> already, cycleAlready;     // 保存已经拿了的cereal
vector<vector<edge>> g;
vector<bool> getCereal;
int firstCereal, extraEdge;


struct edge{
    int cow;
    int to;
    int isFirst;

    edge(int cow, int to, int isFirst): cow(cow), to(to) , isFirst(isFirst){}
}

int flag;

void findCycle(int cur, int prev){
    if(cycleAlready.find(cur) != cycleAlready.end()) return;
    cycleAlready.insert(cur);

    for(edge next: g[cur]){
        if(cycleAlready.find(next.to) != cycleAlready.end()){
            if(firstCereal==-1 && next.to != pre){
                if(next.isFirst){   // 如果这条边是 cur <- next
                    firstCereal = next.to;  // 那就取next.to
                }else{
                    firstCereal = cur;
                }

                extraEdge = next.cow;
                permutation.push_back(next.cow);
                
            }
        }else{
            findCycle(next.to, cur);
        }
    }

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
    // inDegree.resize(n);     // 这里的内存问题？
    for(int i=0; i<=m; i++) {
        r.push_back(i);
        cow[{i,i}] = i;
        g.push_back({});
        getCereal.push_back(false);
    }
    for(int i=1; i<=n; i++){
        int f,s;
        cin>>f>>s;
        r[find(s)] = r[find(f)];    // build disjoint-set
        g[f].push_back(edge(i, s, true));
        g[s].push_back(edge(i, f, false));
    }

    for(int i=1; i<=m; i++){    // 遍历所有cereal
        firstCereal = -1;
        extraEdge = -1;
        findCycle(i, -1);
        if(flag){
            dfs(find(i));
        }else{
            dfs(i);
        }
    }


    cout<<ans<<endl;
    for(auto k: permutation) cout<<k<<endl;
    cout<<endl;
    for(auto it: cow) cout<<it.first[0]<<" "<<it.first[1]<<endl;
}
