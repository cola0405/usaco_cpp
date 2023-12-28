// combination(40,10)  费劲
// C(40, 10) = 847,660,528 加上递归 -- 奔10^9去了
// C(20, 10) = 184,756

// 2_1.cpp 把C(40,20) 拆分成了 C(20,x1) + C(20,x2) -- 起码在本地十几秒能跑完了

#include<bits/stdc++.h>
using namespace std;

// int k;
int n, cnt1, cnt2, cnt;
int xg, yg;
long long totalX=0, totalY=0;
long long leftX=0,leftY=0;
long long rightX=0,rightY=0;

vector<pair<int, int>> ins;
unordered_map<int, unordered_map<long long, unordered_map<long long, int>>> record1, record2; // [left][x][y]
int ans[41];

void combination(vector<int>& inx, int start, int end, int m){    // 搜索所有可行的方案
    if(inx.size() == m){
        long long curX=0, curY=0;
        for(auto i: inx){
            curX += ins[i].first;
            curY += ins[i].second;
        }
        if(end == n){
            for(auto it: record1){
                int left = it.first;
                if(record1[left][xg-curX][yg-curY]){
                    ans[left+m] += record1[left][xg-curX][yg-curY];
                }
                // 相同大小的会轮到的，不需要在这里阴阳算
                if(m != (n-(n/2)-m) && record1[left][xg-(rightX-curX)][yg-(rightY-curY)]) {
                    ans[left + (n-(n/2)-m)] += record1[left][xg-(rightX-curX)][yg-(rightY-curY)];
                }
            }
            
        }
        else{
            record1[m][curX][curY] += 1;
            if(m != n/2-m){
                record1[n/2-m][leftX-curX][leftY-curY] += 1;
            }
            
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
    // freopen("2.in", "r", stdin);
    // freopen("2.out", "w", stdout);
    
    cin>>n;
    cin>>xg>>yg;

    for(int i=0; i<n; i++){
        int x,y;
        cin>>x>>y;
        ins.push_back(make_pair(x,y));
        if(i<n/2){
            leftX += x;
            leftY += y;
        }else{
            rightX += x;
            rightY += y;
        }
    }

    record1[0][0][0] = 1;
    record1[n/2][leftX][leftY] = 1;
    record2[0][0][0] = 1;
    record2[n-n/2][rightX][rightY] = 1;
    vector<int> v;
    // 在这个程序的基础上优化掉k -- 构造好两个record 后 ans[k1+k2]
    // 这样需要遍历record1中所有的点 -- C(20,5) * C(20,5) -- 10^8 不可行 -- 递归中更新ans吧
    for(int k=1; k<=n/4; k++){
        combination(v, 0, n/2, k);
    }
    for(int k=1; k<=(n-n/2)/2; k++){
        combination(v, n/2, n, k);
    }

    if(leftX==xg && leftY==yg) ans[n/2]++;
    if(rightX==xg && rightY==yg) ans[n-n/2]++;

    for(int i=1; i<=n; i++) cout<<ans[i]<<endl;
}