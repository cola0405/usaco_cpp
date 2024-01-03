// 递归
// O(log(max(a,b)) -- 虽然是递归但是每次只走一个分支
// 把问题通过递归统一转换成 "大->小" 的问题 -- 因为 "大->小" 的方法很有限 -- 只有 /2 -- 即是限制又是有力工具
// 这里要注意的就是在转换时，如果是把 "小->大" 转化为 "大->小" -- 对应的操作会发生改变 -- 变成-1
// 拿一个测试用例代入就知道怎么回事了

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// 求a到b的最小操作次数
ll op(ll a, ll b, int cnt, int d){      // d 表示当前的操作是 +1还是-1
    if(a == b) return cnt;
    if(b > a){
        ll tmp = a;
        a = b;
        b = tmp;
        d *= -1;    // 只在swap时才会改变符号
    }

    if(d == 1){
        if(a%2 == 1){
            a++;
            cnt++;
        }
        return op(a/2, b, cnt+1, d);    // 如果当前d=1, 那缩小的方式就只有一种
    }
    else if(d == -1){
        ll subtract = cnt + (a-b);    // 从a一步一步走到b
        if(a%2 == 1){
            a--;
            cnt++;
        }
        // 这里是算法最关键的地方，当d=-1时，有两种缩小的方式 -- 减法、/2 -- 取其中的最小值
        return min(subtract, op(a/2, b, cnt+1, d));     
    }
    return 0;
}

int main(){
    // freopen("1.in", "r", stdin);
    // freopen("1.out", "w", stdout);

    int n;
    cin>>n;
    for(int r=0; r<n; r++){
        ll a,b;
        cin>>a>>b;
        cout<<op(a,b,0,1)<<endl;
    }
}