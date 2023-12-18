// first -> second 作一个 "假无向图" （添加双向边，但是有额外标志位来表明方向）
// vertex 表示燕麦
// edge 表示牛

// (1) 如果 E < V，无环，dfs 选出牛即可
// (2) 如果 E = V，dfs 找出构成环的最后一边，先选这条边，然后 dfs
// (3) 如果 E > v，dfs 找出构成环的最后一边，先选这条边，然后 dfs，需要额外把吃不到的牛也加入到队列（fs都已经被吃了）

#include<bits/stdc++.h>
using namespace std;

int n,m,f,s,fisrtCereal, theCow;
unordered_set<int> usedCereal, cycleDetect;
vector<int> cowOrder;
vector<bool> mark = {false};
// unordered_map<int, vector<int>> g;   // value 不用set，可能会漏掉一些边
// unordered_map<int, unordered_map<int, int>> cow;      // 用这种方法标记的话，如果有fs重复的牛，那就丢失了

struct edge{
    int cow;
    int to;
    int isFirst;
    edge(int cow, int to, int isFirst): cow(cow), to(to), isFirst(isFirst){};
};
vector<vector<edge>> edges;     // 记录所有边，就不会有丢失的问题了

void doExtra(int curCereal, int prevCereal){ 
    // 不用额外设置return条件，因为for循环内有 if 分支没有继续递归
    cycleDetect.insert(curCereal);
    for(auto next: edges[curCereal]){
        if(cycleDetect.find(next.to) != cycleDetect.end()){
            if(fisrtCereal == -1 && next.to != prevCereal){    // 排除a->b b->a 的情况，这可以直接dfs
                fisrtCereal = next.isFirst ? curCereal : next.to;
                theCow = next.cow;
                cowOrder.push_back(theCow);
                mark[theCow] = true;    // mark the cow already eat cereal
                return;     // 找出一条extra即可，剩下的交给dfs
            }
        }else{
            doExtra(next.to, curCereal);
        }
    }
}

void dfs(int curCreal){
    // 不直接return，因为可能是其他节点到cur的
    usedCereal.insert(curCreal);
    for(auto next: edges[curCreal]){
        if(usedCereal.find(next.to) == usedCereal.end() && next.cow != theCow){
            cowOrder.push_back(next.cow);   // 这里能入队列的都是不挨饿的 (f或s中的一个还有得吃)
            mark[next.cow] = true;  // 只有fs中还有一者存在时牛才有得吃
            dfs(next.to);   // 某节点被取了，那接着就应该优先取它的first
        }
    }
}

int main(){
    // freopen("3.in", "r", stdin);
    // freopen("3.out", "w", stdout);

    cin>>n>>m;
    for(int i=0; i<=m; i++){
        edges.push_back({});
    }
    for(int i=1; i<=n; i++){
        cin>>f>>s;
        // 不能简单地只建立单向图,因为存在 first second 的先后问题
        edges[f].push_back(edge(i,s,true)); 
        edges[s].push_back(edge(i,f,false));
        mark.push_back(false);
    }

    for(int i=1; i<=m; i++){    // 查看每个cereal的情况
        if(usedCereal.find(i) != usedCereal.end()) continue;

        theCow = -1;
        fisrtCereal = -1;    // 后续dfs的起点
        doExtra(i, -1);  // 找出一条extra即可，剩下的交给dfs
        if(fisrtCereal != -1){
            dfs(fisrtCereal);    // 有firstCereal 则从这里开始 dfs
        }else{
            dfs(i);     // 否则就从当前cereal开始dfs
        }
    }

    int ans = 0;
    for(int i=1; i<=n; i++){
        if(!mark[i]){
            cowOrder.push_back(i);  // 挨饿的牛最后也要入队列 ！！！
            ans++;
        }
    }
    cout<<ans<<endl;
    for(auto cow: cowOrder) cout<<cow<<endl;
}