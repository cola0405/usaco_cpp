// 二分upper_bound + 并查集(确认是否同一连通分量) -- 用dfs确认也可以
#include <bits/stdc++.h>
using namespace std;

int N,M;
vector<int> cows = {0};  // 把index化1
vector<vector<int>> path;
unordered_set<int> diff;
vector<int> r;  // 并查集

int find(int node){
    if(node == r[node]) return node;
    r[node] = find(r[node]);
    return r[node];
}

int valid(int width){
    r.clear();
    for(int i=0; i<=N; i++) r.push_back(i);

    for(auto it: path){
        int a=it[0], b=it[1], c=it[2];
        if(c >= width) r[find(b)] = r[find(a)];  // 以width作为虫洞最低限度
    }

    for(auto pos: diff){
        if(find(pos) != find(cows[pos])) return false;  // 如果pos和cows[pow]在同一连通分量，则可以通过虫洞排好序
    }
    return true;
}

int main(){
    freopen("wormsort.in", "r", stdin);
    freopen("wormsort.out", "w", stdout);
    
    cin>>N>>M;
    for(int i=0; i<N; i++){
        int cow;
        cin>>cow;
        if(cow != i+1) diff.insert(i+1);
        cows.push_back(cow);
    }
    if(diff.size() == 0){
        cout<<-1<<endl;
        return 0;
    }

    vector<int> wh;
    for(int i=0; i<M; i++){
        int a,b,w;
        cin>>a>>b>>w;
        path.push_back({a,b,w});
        wh.push_back(w);
    }
    sort(wh.begin(), wh.end());

    // binary seach
    int low=0, high=wh.size()-1;
    while(low<high){
        int mid = (low+high+1)/2;   // upper bound
        if(valid(wh[mid])){
            low = mid;
        }
        else high = mid-1;
    }
    cout<<wh[low]<<endl;
    
}