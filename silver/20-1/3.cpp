#include <bits/stdc++.h>
using namespace std;

int N,M;
vector<vector<int>> path;
unordered_set<int> diff;

int valid(int width){
    unordered_set<int> group;
    for(auto it: path){
        int a=it[0], b=it[1], c=it[2];
        if(c >= width){     // 看大于或等于当前width的通道能够消除哪些位置
            group.insert(a);
            group.insert(b);
        }
    }
    for(auto pos: diff){     
        if(group.find(pos) == group.end()) return false;
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
        int mid = (low+high+1)/2;
        if(valid(wh[mid])){
            low = mid;
        }
        else high = mid-1;
    }
    cout<<wh[low]<<endl;
    
}