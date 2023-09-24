#include <bits/stdc++.h>
using namespace std;

int main(){
    freopen("mootube.in", "r", stdin);
    freopen("mootube.out", "w", stdout);

    int n,q;
    cin>>n>>q;
    unordered_map<int, unordered_map<int, int>> g;
    for(int i=0; i<n-1; i++){
        int v1,v2,r;
        cin>>v1>>v2>>r;
        g[v1][v2] = r;
        g[v2][v1] = r;
    }

    for(int i=0; i<q; i++){
        int k,v;
        cin>>k>>v;
        
        vector<bool> available(n+1, true);
        available[v] = false;
        queue<int> q;
        q.push(v);
        int res = 0;
        
        while(!q.empty()){
            int top = q.front();
            q.pop();
            
            for(auto node: g[top]){
                if(available[node.first] && node.second >= k){
                    q.push(node.first);
                    res += 1;
                    available[node.first] = false;
                }
            }

        }
        cout<<res<<endl;
    }

}