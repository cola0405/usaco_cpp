// A gate can be added to any unit-length segment of fence
/*
            ....
            .  .
            ....
     ........      
     .      .
     .      .
     ........
 */
// 题目测试用例如上图，最少需要两个门，来打开这两个封闭区域
// 题目转化为，求总共有多少个封闭的区域 -- flood fill

// 上万层递归顶不住，那就用非递归的方式
// 二维数组模拟fence时，step=2

#include<bits/stdc++.h>
using namespace std;

int farm[2001][2001];
unordered_map<char, pair<int,int>> d = {{'N', {-1,0}}, {'S', {1,0}}, {'W',{0,-1}}, {'E',{0,1}}};

// 上万层的递归顶不住
// void dfs(int i, int j){      
//     ...
// }

void bfs(int i, int j){     // 非递归的才可以
     queue<pair<int,int>> q;
     q.push(make_pair(i,j));
     while(!q.empty()){
        pair<int,int> top = q.front();
        q.pop();
        int x=top.first, y=top.second;
        if(x<0 || x>2000 || y<0 || y>2000 || farm[x][y]==1 || farm[x][y]==2) continue;
        farm[x][y] = 2;
        q.push(make_pair(x+1,y));
        q.push(make_pair(x-1,y));
        q.push(make_pair(x,y+1));
        q.push(make_pair(x,y-1));
     }
}

int main(){
    freopen("gates.in", "r", stdin);
    freopen("gates.out", "w", stdout);

    int n;
    cin>>n;
    int x=1000,y=1000;
    for(int i=0; i<n; i++){
        char c;
        cin>>c;
        for(int j=0; j<2; j++){     // 二维数组模拟fence时，要注意 "NESW" 中间其实是应该有一个空位的
            x += d[c].first;
            y += d[c].second;
            farm[x][y] = 1;
        }
        
    }

    int ans = -1;   // 初始的一次bfs不算
    for(int i=0; i<=2000; i++){
        for(int j=0; j<=2000; j++){
            if(farm[i][j] == 0){
                bfs(i,j);
                ans++;
            }
        }
    }
    cout<<ans<<endl;
}