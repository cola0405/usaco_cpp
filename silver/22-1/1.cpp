// 递归模拟
// O(log(max(a,b))

// 正向从小到大转化的问题比较复杂，无法确认是+* 还是*+, 还是+*+
// 然而，从大到小的转化问题就简单得多，贪心选项是尽可能用/
// 从小到大无法确认是因为+*的收益可能会更大
// 但是大到小，则是尽早/收益才大

// 正向如果要模拟的话，时间复杂度就高了
// 反向模拟则时间复杂度则约是O(logn) -- 一直都在/
// 所以思考，是否可以把正向问题转化为反向问题呢？
// 2 -> 13 可以转而从 13 -> 2 允许的操作有: / 和 -
// 原理是: (2+1)*2*2+1 = 13 等效于 (13-1)/2/2-1 = 2 操作次数都为 4

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// 求a到b的最小操作次数
ll op(ll a, ll b, int cnt, int d){      // d 表示当前a、b有没有进行交换
    if(a == b) return cnt;
    if(a < b){           // 统一把问题转化为 "大->小"
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
        return op(a/2, b, cnt+1, d);    // 尽可能/ 另外，当a/2小于b时，则进行swap
    }
    else if(d == -1){                  // swap后, 支持操作: / -
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