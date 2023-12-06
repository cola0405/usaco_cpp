// 全连接检测
// 无向图，任意选一点bfs，能遍历全部节点，则是全连接

#include <bits/stdc++.h>
using namespace std;

int n,m;
unordered_set<int> closed;
unordered_map<int, unordered_set<int>> path; 

int bfs(){
    int barn;
    for(barn=1; barn<=n; barn++){
        if(closed.find(barn) == closed.end()) break;
    }
    vector<int> stack {barn};
    unordered_set<int> already;
    while(!stack.empty()){
        int top = stack.back();
        stack.pop_back();
        already.insert(top);
        for(int nxt: path[top]){
            if(already.find(nxt) == already.end() && closed.find(nxt) == closed.end()){
                stack.push_back(nxt);
            }
        }
    }

    return already.size();
}

int main(){
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);
    
    cin>>n>>m;
    
    for(int i=0; i<m; i++){
        int from, to;
        cin>>from>>to;
        path[from].insert(to);
        path[to].insert(from);
    }

    for(int i=0; i<n; i++){
        if(bfs() == n-i){
            cout<<"YES"<<endl;
        }else{
            cout<<"NO"<<endl;
        }
        int close;      // 调准顺序为了取到一开始的状态和省去最后的状态
        cin>>close;
        closed.insert(close);
    }
}