// BFS 解决最短路问题

// 从Barn往回bfs，直到回到Laser为止

#include <bits/stdc++.h>
using namespace std;

int n,Lx,Ly,Bx,By;
vector<pair<int,int>> fence;
queue<vector<int>> q;
unordered_map<int, vector<int>> X, Y;

int solve(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("lasers.in", "r", stdin);
    freopen("lasers.out", "w", stdout);

    cin>>n>>Lx>>Ly>>Bx>>By;
    X[Lx].push_back(Ly);
    Y[Ly].push_back(Lx);
    fence.resize(n);
    for(int i=0;i<n;i++){
        cin>>fence[i].first>>fence[i].second;
        X[fence[i].first].push_back(fence[i].second);
        Y[fence[i].second].push_back(fence[i].first);
    }
    q.push({0, Bx, By});
    while(!q.empty()) {
        int size = q.size();
        while(size--) {
            int cost=q.front()[0], x=q.front()[1], y=q.front()[2];  
            q.pop();
            if(x==Lx && y==Ly) return cost-1;
            while(!X[x].empty()){       // the points with same x
                int y1 = X[x].back();
                X[x].pop_back();            // 每个点只访问一次(一个镜子用两次能有什么改变呢)，所以bfs时间复杂度是O(n)
                q.push({cost+1, x, y1});    // 不会有矛盾，具体可以结合题目给的测试用例验证
            }
            while(!Y[y].empty()){
                int x1 = Y[y].back();
                Y[y].pop_back();
                q.push({cost+1, x1, y});
            }
        }
    }
    return -1;
}
int main() {
    cout<<solve()<<endl;
    return 0;
}