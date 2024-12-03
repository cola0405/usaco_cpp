// dfs + directed graph with multi path

// the keypoint is to build the graph
// just record the avaliable flights and dfs them
// the total time complexity is O(m) -- the number of the flights

#include <iostream>
#include <unordered_map>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

int n;
unordered_map<int, deque<vector<int>>> fl;      // graph
vector<int> ans(2e5+1, 2e9);
vector<int> a(2e5+1);

void dfs(int cur_time, int previous, int cur){     // cur: current city
    ans[cur] = min(ans[cur], cur_time);
    while(fl[cur].size()){
        auto x = fl[cur].front();
        int t1=x[0], t2=x[1], t=x[2];
        int depature_time = cur_time;
        if(previous != -1) depature_time += a[cur];       // add layover time, except the first flight
        if(depature_time <= t1){
            fl[cur].pop_front();                   // optimization
            dfs(t2, cur, t);
        } else return;      // after sorting, current t1 is the latest flight, there is no need to check the following flights
    }
}

int main()
{
    // freopen("3.in", "r", stdin);
    // freopen("3.out", "w", stdout);

    int m;
    int f,t1,t,t2;
    cin>>n>>m;
    for(int i=0; i<m; i++){
        cin>>f>>t1>>t>>t2;
        fl[f].push_back({t1,t2,t});
    }
    for(int i=1; i<=m;i++) cin>>a[i];

    // sort the flights in decending order
    for(auto &x: fl) sort(x.second.begin(), x.second.end(), greater<>());
    dfs(0, -1, 1);
    for(int i=1; i<=n; i++){
        if(ans[i] == 2e9) cout<<-1<<endl;
        else cout<<ans[i]<<endl;
    }
    return 0;
}
