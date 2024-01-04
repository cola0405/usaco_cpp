// 单调栈解决扔飞盘问题 -- 结合实际的例子动手推导，找规律 -- 脑子不够用
// 双重for循环累计但是这里是10^5 O(n^2) 超时 -- 详细看2_1.cpp

// 优化方案一个大方向是快速定位endpoint -- 快速找到之后第一个比h[i]大的数，要统计的距离肯定在这个范围内
// 从后往前更新max不行 -- 只能用来找h[i]之后最大的数
// 除此以外也没有什么数据结构能够帮助优化这个问题
// 那就再转换问题 -- 遍历h, 然后看之前是否有比它更小的，一旦有left比cur小 -- 那cur就是left的endpoint
// 看之前是否有比它更小的 -- 不难想到优先队列、单调栈 -- 单调栈效率能更高
// 找到一对endpoint pair 后找到就可以pop -- 其不可能与cur之后的牛扔飞盘

// 单调栈可以快速定位endpoint，接下来应该思考范围内的 pair 如何统计
// 需要把注意力放到单调栈是否有可以利用的规律
// 基于前面的pop操作，单调栈有了一个很有意思的性质
// 单调栈左边的元素就是在左边的 -- 我们不会往单调栈放入比top更大的元素
// 那也就是说 -- cur能与单调栈内所有元素扔飞盘！ -- 每次遍历都是有效的，和之前的O(n^2) 有一些区别 -- 虽然是双重循环但是不一定会超时

#include<bits/stdc++.h>
using namespace std;

int n;
int h[300001];

int main(){
    // freopen("2.in", "r", stdin);
    // freopen("2.out","w", stdout);

    cin>>n;
    unordered_map<int, int> inx;
    for(int u=1; u<=n; u++){
        cin>>h[u];
        inx[h[u]] = u;
    }
    long long ans = 0;    // [i] 和 [i+1]
    vector<int> st;  // 单调栈 -- top是min
    for(int j=1; j<=n; j++){
        // while看栈顶有哪些endpoint pair -- 找到就可以pop -- 其不可能与cur之后的牛扔飞盘，不需要留在栈里
        while(!st.empty() && h[j] > st.back()){
            int i = inx[st.back()];
            ans += j-i+1;
            st.pop_back(); 
        }
        // 对单调栈内各元素进行距离统计 -- 单调栈从小到大顺序遍历
        for(auto it=st.rbegin(); it!=st.rend(); it++){
            int height = *it, i = inx[height];
            ans += j-i+1;
            if(height > h[j]) break;    // 只要没遇到比cur更高的，那就都可以扔飞盘
        }
        st.push_back(h[j]);
    }
    cout<<ans<<endl;
}