// 题目问任选 k 条指令, 能到目的地的有几种选法 (k=1~N)
// combination问题 -- C(40,20) -- 10^10  需要优化

// 对combination进行拆分 
// 把C(40,20) 拆分成左右两部分，分别计算 C(20,20) 和 C(20,20) -- 10^6
// 然后再对 ans 进行统计 -- ans[left+right]

// 这里要注意数据结构的设计 -- offset[(x,y)][m]
// 目的地pair(x,y) 作key, 再存一个字典 {m: count} -- {已选ins数: 不同方案的数量}


// 如果把数据结构设计成 map[m][x][y] 三重map会有大问题
// 节点数量会多很多 -- 同一位置在不同 m 会有重复记录
// 内存到1G了。。。 -- 报了 "!" 的错误 -- 内存超限 -- 不可能把C(40,20)所有点都存起来
// 但是 offset[(x,y)][m] 则会对点进行去重


#include<bits/stdc++.h>
using namespace std;

int n;
int xg, yg;
long long ans[41];
vector<pair<int, int>> ins;

bool cmp(const pair<int,int>& a, const pair<int,int>& b){
    return a.first < b.first;
}

struct hs {     // hash for pair
	long long operator()(const pair<int,int> &p) const {
		return p.first * 239 + p.second;
	}
};
// offset[(x,y)][m] -- 偏移(x,y) 需要的ins的数量
unordered_map<pair<int,int>, unordered_map<int,long long>, hs> offset1, offset2; 

// m -- 目标选m个, start和end -- 选取的区间, (x,y) -- 当前位置
void combination(int selected, int start, int end, int m, long long x, long long y){    // 搜索所有可行的方案
    if(selected == m){
        if(end == n){
            offset2[make_pair(x,y)][m] += 1;    // [(x,y)][left] -- 左边选了left个，使得位置偏移(x,y)
        }
        else{
            offset1[make_pair(x,y)][m] += 1;    // [(x,y)][right] -- 右边选了right个，使得位置偏移(x,y)
        }
        return;
    }

    for(int i=start; i<end; i++){
        combination(selected+1, i+1, end, m, x+ins[i].first, y+ins[i].second);
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
    }
    offset1[make_pair(0,0)][0] = 1;
    offset2[make_pair(0,0)][0] = 1;

    // 把C(40,20) 拆分成左右两部分，分别计算 C(20,20) 和 C(20,20)
    for(int k=1; k<=n/2; k++) combination(0, 0, n/2, k, 0,0);
    for(int k=1; k<=n-n/2; k++) combination(0, n/2, n, k, 0,0);

    // 然后再进行 ans 的统计 -- ans[left+right]
    for(auto &[point, d]: offset1){     // C(20,10) 为最大 -- 才10^6
        long long x = xg-point.first, y = yg-point.second;
        if(offset2.find(make_pair(x,y)) != offset2.end()){
            for(auto &[left, cnt1]: d){     // 顶多20
                for(auto &[right, cnt2]: offset2[make_pair(x,y)]){  // 顶多20 -- 故不超时
                    ans[left+right] += cnt1*cnt2;
                }
            }
        }
    }

    for(int i=1; i<=n; i++) cout<<ans[i]<<endl;
}