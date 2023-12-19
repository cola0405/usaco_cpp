// dfs 打标签考察连通分量交叉的情况
// 有两种不同的种子，分别标记为1或者2

// 如果没有限制条件 -- label[i] = 0 方案数*2
// 如果有限制条件 -- 相关的节点无法翻倍，同时还要检测是否有矛盾点 -- 直接返回 0

// 如何检测矛盾点 -- 看同一连通分量中是否有restriction造成的矛盾点
// 看 dfs 过程中是否都符合当前连通分量的规则


#include<bits/stdc++.h>
using namespace std;

int n,m;
vector<int> SEdge[100001], DEdge[100001];
int label[100001];

bool dfs(int cur, int l){   // 看 dfs 过程中是否都符合当前连通分量的规则
    label[cur] = l;
     for(auto to: SEdge[cur]){
        if(label[to] == 3-l) return true;   // 3-1=2, 3-2=1 用来检查标记
        if(label[to] == 0 && dfs(to, l)) return true;   
     }
     for(auto to: DEdge[cur]){
        if(label[to] == l) return true;
        if(label[to] == 0 && dfs(to, 3-l)) return true;
     }
     return false;
}


int main(){
    freopen("revegetate.in", "r", stdin);
    freopen("revegetate.out", "w", stdout);

    cin>>n>>m;

    for(int i=0; i<m; i++){
        char type;
        int a,b;
        cin>>type>>a>>b;
        if(type == 'S'){
            SEdge[a].push_back(b);  // 保存双向，便于环检测
            SEdge[b].push_back(a);
        }else{
            DEdge[a].push_back(b);
            DEdge[b].push_back(a);
        }
    }

    int ans = 0;
    for(int i=1; i<=n; i++){
        if(!label[i]){
            if(dfs(i, 1)){      // assume the label start from 1
                cout<<0<<endl;
                return 0;
            }
            ans++;  // 每个连通分量都是独立的，都可以翻一倍
        }
    }

    cout<<1;
    for(int i=0;i<ans;i++) cout<<0;
    cout<<endl;
}

/*
4 4
S 1 2
D 3 2
D 1 4
S 3 4
*/

/*
4 4
S 1 2
D 3 2
D 1 4
D 3 4
*/

/*
4 5
D 1 2
S 2 3
S 3 4
S 4 1
S 1 2

1 2 有S有D -- 一旦有不可行的，就不可能  -- 不能用unordered_set边去重
*/