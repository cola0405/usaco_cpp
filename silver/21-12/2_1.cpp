// 相当于是找首末两个连通分量之间是搭一条路或两条路，使得花费最小
// ps: 题目说了最多搭两条路


// 观察太极的图案
// 不一定是min与max
// N=10 连通分量(1,5,6) 和 (4,10), 此时 "4-5" 是最佳选择，与min max 都无关
// 那怎么找两个连通分量之间的最短路呢

#include<bits/stdc++.h>
using namespace std;

int N,M;
int l,r;
vector<int> u;
unordered_map<int, vector<int>> components;
int find(int x){
    if(x == u[x]) return x;
    u[x] = find(u[x]);
    return u[x];
}

int getCost(int a, int b){
    if(find(a) == find(b)) return 0; 
    vector<int>& q1 = components[find(a)];
    vector<int>& q2 = components[find(b)];

    int minGap = INT_MAX;
    int i=0,j=0;
    for(i=0; i<q1.size(); i++){
        while(j<q2.size() && q2[j]<q1[i]){
            minGap = min(minGap, q1[i]-q2[j]);
            j++;
        }
    }

    i=0,j=0;
    for(j=0; j<q2.size(); j++){
        while(i<q1.size() && q1[i]<q2[j]){
            minGap = min(minGap, q2[j]-q1[i]);
            i++;
        }
    }
    return minGap*minGap;
}

int main(){

    // freopen("2.in", "r", stdin);
    // freopen("2.out", "w", stdout);

    int T;
    cin>>T;
    for(int y=0; y<T; y++){
        cin>>N>>M;
        // if(y == 3)cout<<N<<"************"<<M<<endl;
        u.clear();
        for(int i=0; i<=N; i++) u.push_back(i);
        for(int i=0; i<M; i++){
            int a,b;
            cin>>a>>b;
            u[find(b)] = u[find(a)];
        }

        // build components
        components.clear();
        for(int i=1; i<=N; i++){
            components[find(i)].push_back(i);
        }

        // build a path
        int cost = getCost(1,N);
        if(cost == 0){
             cout<<0<<endl;
            continue;
        }

        // build two path
        unordered_set<int> already{find(1), find(N)};
        for(int mid=2; mid<N; mid++){   // 尝试所有中转的连通分量
            if(already.find(find(mid)) != already.end()) continue;
            cost = min(cost, getCost(1,mid) + getCost(mid, N));
            already.insert(find(mid));
        }
        cout<<cost<<endl;
    }
}