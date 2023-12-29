// combination(40,10)  费劲
// C(40, 10) = 847,660,528 加上递归 -- 奔10^9去了
// C(20, 10) = 184,756

// 2_1.cpp 把C(40,20) 拆分成了 C(20,x1) + C(20,x2) -- 起码在本地十几秒能跑完了
// 可以在combination 的参数列表中就把 x y 累积起来 -- 2_2_2_1.cpp
// 优化过后record1 和record2 的构造过程其实很快
// 麻烦的是通过两个 hashset 完成 ans 的统计


// 内存到1G了。。。 -- 报了 "!" 的错误 -- 内存超限 -- 不可能把C(40,20)所有点都存起来
// 阴阳法的那部分不存起来 -- 用时再算

// 答案正确，阴阳法动态算，但是内存只降到800MB 但仍然超限，而且运行时间是十多秒
// 只过了7个测试用例

#include<bits/stdc++.h>
using namespace std;

// int k;
int n;
int xg, yg;
long long leftX=0,leftY=0;
long long rightX=0,rightY=0;

vector<pair<int, int>> ins;
unordered_map<int, unordered_map<long long, unordered_map<long long, int>>> record1, record2; // [left][x][y]
int ans[41];

void combination(vector<int>& inx, int start, int end, int m, long long x, long long y){    // 搜索所有可行的方案
    if(inx.size() == m){
        if(end == n){
            record2[m][x][y] += 1;
        }
        else{
            record1[m][x][y] += 1;
        }
        return;
    }

    for(int i=start; i<end; i++){
        inx.push_back(i);
        combination(inx, i+1, end, m, x+ins[i].first, y+ins[i].second);
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
    for(int k=1; k<=n/4; k++){
        combination(v, 0, n/2, k, 0,0);
    }
    for(int k=1; k<=(n-n/2)/2; k++){
        combination(v, n/2, n, k, 0,0);
    }
    for(int left=0; left<=n/4; left++){
        for(int right=0; right<=(n-n/2)/2; right++){
            for(auto it: record1[left]){
                long long curx = it.first;
                for(auto it1: record1[left][curx]){
                    long long cury = it1.first;
                    long long x=xg-curx, y=yg-cury;
                    // int cnt = it1.second * record2[right][x][y];
                    if(record2[right][x][y]){
                        ans[left + right] += it1.second * record2[right][x][y];
                    }
                    if(right != (n-n/2-right) && record2[right][rightX-x][rightY-y]){     // 在record的阴没有，才看阳
                        ans[left + (n-n/2-right)] += it1.second * record2[right][rightX-x][rightY-y];
                    }

                    x=xg-(leftX-curx), y=yg-(leftY-cury);
                    if(left != n/2-left && record2[right][x][y]){   // 挑的数量相等，避免重复算
                        ans[(n/2-left) + right] += it1.second * record2[right][x][y];
                    }
                    if((left != n/2-left) && (right != (n-n/2-right)) && record2[right][rightX-x][rightY-y]){     // 在record的阴没有，才看阳
                        ans[(n/2-left) + (n-n/2-right)] += it1.second * record2[right][rightX-x][rightY-y];
                    }
                }
            }
        }
    }

    for(int i=1; i<=n; i++) cout<<ans[i]<<endl;
}