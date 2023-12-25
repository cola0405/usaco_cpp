// 单调队列

#include<bits/stdc++.h>
using namespace std;

bool cmp(const pair<int,int>& a, const pair<int,int>& b){
    return a.first > b.first;
}

int n,m,k;
int main(){
    // freopen("1.in", "r", stdin);
    // freopen("1.out", "w", stdout);

    cin>>n>>m>>k;
    vector<pair<int, int>> cows;
    for(int i=0; i<n; i++){
        int w,a;
        cin>>w>>a;
        cows.push_back(make_pair(w,a));
    }
    sort(cows.begin(), cows.end(), cmp);
    deque<pair<int, int>> deq = {{INT_MAX, m}};     // 压缩单调队列后，空间ok了，但是仍然超时，接着压缩操作
    int ans = 0;
    int pile = 0;
    for(auto it: cows){
        int w=it.first, a=it.second;
        for(int i=0; i<a; i++){
            if(w+k <= deq.front().first){
                ans++;
                deq.front().second--;
                if(deq.front().second == 0) deq.pop_front();
                if(w == deq.back().first) deq.back().second++;
                else deq.push_back(make_pair(w,1));
            }
        }
    }
    cout<<ans<<endl;
}