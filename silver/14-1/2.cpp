// 找最短路问题不好写，那就转换为二分+bfs
// 以当前D去 bfs，如果可达所有节点，则继续二分
// 时间复杂度顶多 10^5  O(nmlogn) 

// 竞赛中的数据结构
// (1) 能声明固定长度就声明固定长度，内存申请更消耗时间
// (2) 能用pair就用pair
// (3) 能用标志位就不用unordered_set

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> d = {{0,1},{0,-1},{1,0},{-1,0}};
int height[501][501], wp[501][501];
bool visited[501][501];     // 能声明固定长度就声明固定长度，内存申请更消耗时间
int m,n;
int wi,wj;

bool bfs(int D){
    for(int i=0; i<m; i++){     // reset visited
        for(int j=0; j<n; j++){
            visited[i][j] = false;
        }
    }

    queue<pair<int, int>> q;
    q.push(make_pair(wi, wj));  // 能用pair就用pair
    while(!q.empty()){
        pair<int, int> top = q.front();
        q.pop();
        int i=top.first, j=top.second;
        for(auto it: d){
            int nextI=i+it[0], nextJ=j+it[1];
            if(nextI<0 || nextI>=m || nextJ<0 || nextJ>=n || visited[nextI][nextJ] || abs(height[i][j]-height[nextI][nextJ]) > D) continue;
            visited[nextI][nextJ] = true;   // 一定得马上标记
            q.push(make_pair(nextI, nextJ));
            
        }
    }

    for(int i=0; i<m; i++){     // count the visited waypoints
        for(int j=0; j<n; j++){
            if(wp[i][j] && !visited[i][j]) return false;
        }
    }
    return true;
}

int main(){
    freopen("ccski.in", "r", stdin);
    freopen("ccski.out", "w", stdout);

    cin>>m>>n;
    for(int i=0; i<m; i++){     // build graph
        for(int j=0; j<n; j++){    
            cin>>height[i][j];
        }
    }
    
    for(int i=0; i<m; i++){     // build waypoint
        for(int j=0; j<n; j++){
            cin>>wp[i][j];
            if(wp[i][j]) {  // record the start waypoint
                wi = i;
                wj = j;
            }
        }
    }

    int low=0, high=1e9;
    while(low<high){
        int mid = (low+high)/2;
        if(bfs(mid)) high = mid;
        else low = mid+1;
    }
    cout<<low<<endl;
}