// 草稿找规律
// 字符串涉及的操作无非就两种: 重复、偏移
// 观察到如此大的数据范围，我们不难想到这题可能需要log的时间复杂度
// 进而想到 /2 的操作
// 接下来就需要处理偏移问题, 这个需要在草稿纸上找规律
// COW
// COWWCO
// COWWCOOCOWWC
//        |
//        8
// 第8个C其实是对应到第1个C
// 这是有规律可循的
// 右边为不做偏移的字符串复制 COWWCO | COWWCO 
//                                   |
// 这里标注的C 其实会与一个参数有很大的关系 ——> 上一个字符串的末尾的位置end ——> 3 6 12 ...
// 7-6=1, 表示标注C 其实是上一个字符串index = 1 的位置
// 然后考虑一下偏移offset=1, 从而对于测试用例的n=8 会有 8-6-1=1
// 表示n=8 位置的字符，其实是上一个字符串index=1 的位置，该index <= 3, 不需要再重复往上一个字符串找
// 所以得到n=8 的字符是C

// 这里又一个特殊情况要处理: 当n-end-1=0 时, 其实是对应上一个字符串的最后一个

// 左边最近的end 为关键点

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    freopen("cowcode.in", "r", stdin);
    freopen("cowcode.out", "w", stdout);

    string s;
    ll n;
    cin>>s>>n;

    ll end = s.size();
    while(end*2 < n) end *= 2;  // 找到左边最近的end
    while(n > s.size()){
        n = n-end-1;
        if(n == 0) n = end;     // 特殊情况处理
        while(end >= n) end /= 2;
    }
    cout<<s[n-1]<<endl;
    return 0;
}