#include<bits/stdc++.h>
using namespace std;

int t,n,q,c;
int scores[30];
priority_queue<int> pq;
vector<int> waitting;
vector<pair<int,int>> p;

void solve(){
    // init
    while(!pq.empty()) pq.pop();
    waitting.clear();
    p.clear();

    cin>>n>>q>>c;
    for(int i=1; i<=n; i++){
        cin>>scores[i];
    }
    
    for(int i=0; i<q; i++){
        int right,top_inx;
        cin>>right>>top_inx;
        p.push_back(make_pair(right, top_inx));
    }
    sort(p.begin(), p.end());
    
    int cur = 0;
    for(auto& it: p){
        int right = it.first, top_inx = it.second;
        for(int i=cur+1; i<=right; i++){
            if(scores[i] == 0){
                pq.push(1);
                waitting.push_back(i);
            }
            else{
                pq.push(scores[i]);
            }
            cur++;
        }
        
        // 检查窗口到 top_inx 中间有没有 >top
        for(int i=right; i<top_inx; i++){
            if(scores[i] > pq.top()){
                cout<<-1<<endl;
                return;
            }
        }

        if(scores[top_inx] == 0){
            scores[top_inx] = pq.top()+1;
            pq.push(scores[top_inx]);
            cur++;
            if(scores[top_inx] > c){
                cout<<-1<<endl;
                return;
            }
        }
        
        else{
            // 如果当前有top —— 要破坏
            int pq_top = pq.top();
            pq.pop();
            if(pq_top != pq.top()){
                pq.push(pq_top);    // 放回
                if(waitting.empty()){
                    cout<<-1<<endl;
                    return;
                }
                else{
                    scores[waitting.back()] = pq.top();
                    waitting.pop_back();
                    while(!waitting.empty()){
                        scores[waitting.back()] = 1;
                        waitting.pop_back();
                    }
                }
            }
            else{   // 如果当前pq内已经没有top —— 给1
                pq.push(pq_top);
                if(scores[top_inx] <= pq.top()){
                    cout<<-1<<endl;
                }
                while(!waitting.empty()){
                    scores[waitting.back()] = 1;
                    waitting.pop_back();
                }
            }
        }
    }
    for(int i=1; i<=n; i++){
        if(scores[i] == 0) scores[i] = 1;
    }
    cout<<scores[1];
    for(int i=2; i<=n; i++){
        cout<<" "<<scores[i];
    }
    cout<<endl;
}

int main(){
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);

    cin>>t;
    for(int u=0; u<t; u++){
        solve();
    }
}