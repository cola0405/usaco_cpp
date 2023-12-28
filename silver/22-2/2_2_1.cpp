// combination(40,10)  费劲
// C(40, 10) = 847,660,528 加上递归 -- 奔10^9去了
// C(20, 10) = 184,756

// 2_1.cpp 把C(40,20) 拆分成了 C(20,x1) + C(20,x2) -- 起码在本地十几秒能跑完了
// 新的优化思路

#include<bits/stdc++.h>
using namespace std;

int k;
int n, cnt1, cnt2, cnt;
int xg, yg;
long long totalX=0, totalY=0;

vector<pair<int, int>> ins;
unordered_map<int, unordered_map<long long, unordered_map<long long, int>>> record; // [left][x][y]
int ans[41];

void combination(vector<int>& inx, int start, int end, int m){    // 搜索所有可行的方案
    if(inx.size() == m){
        long long curX=0, curY=0;
        for(auto i: inx){
            curX += ins[i].first;
            curY += ins[i].second;
        }
        if(end == n){   // right
            // 利用 hash 来快速看左边有多少种方法可以凑到终点 -- hash已经记录好，不用回溯到源头
            // 只看 k-m 即可
            if(record[k-m][xg-curX][yg-curY]){
                cnt += record[k-m][xg-curX][yg-curY];
            }
        }
        else{  // left
            record[k][curX][curY] += 1;
        }
        return;
    }

    for(int i=start; i<end; i++){
        inx.push_back(i);
        combination(inx, i+1, end, m);
        inx.pop_back();
    }
}

int main(){
    freopen("2.in", "r", stdin);
    freopen("2.out", "w", stdout);
    
    cin>>n;
    cin>>xg>>yg;

    for(int i=0; i<n; i++){
        int x,y;
        cin>>x>>y;
        ins.push_back(make_pair(x,y));
        totalX += x;
        totalY += y;
    }

    record[0][0][0] = 1;
    for(k=1; k<=n; k++){    // 取 k 个
        cnt = 0;
        vector<int> v;
        if(k<=n/2) combination(v, 0, n/2, k);   // 不断完善 left 
        for(int right=0; right<=k; right++){    // 这里求left 有大量的重复，可以试着优化 -- 没用，主要问题不在这
            combination(v, n/2, n, right);
        }
        ans[k] = cnt;
    }

    for(int i=1; i<=n; i++) cout<<ans[i]<<endl;
}