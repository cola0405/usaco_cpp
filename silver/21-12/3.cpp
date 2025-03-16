// difference

// it's impossible to try all nxn pairs
// but we notice that the M<=5000, which actually give us tips
// we can't try every pairs, but we can try every two position!

// it's easy to figure out the total pairs, but how to select the valid pairs
// for this algorithm, we can use difference algorithm, quickly modify [0,2M] -- k

// let's check out the example testcase:
/*

可能的选择：
(1,3) (1,3)  -- 1+1 <= k <= 3+3  -- 区间[2,6] + 1
(1,3) (2,5)  -- 1+2 <= k <= 3+5  -- 区间[3,8] + 1
(2,5) (1,3)  -- 2+1 <= k <= 5+3  -- 区间[3,8] + 1
(2,5) (2,5)  -- 2+2 <= k <= 5+5  -- 区间[4,10] + 1

[0,0,1,3,4,4,4,3,3,1,1]
看似可以用差分解决，但是因为 n = 10^5 O(n^2) 枚举所有(i,j)组合是拿不到满分的
我们需要转化思路，把目光瞄准到 m<=5000 这里
枚举不了所有组合，那我们就统计每个位置的数量
然后使用组合数学+差分的方式求解

要注意的就是这种思路的差分处理和常规的不太一样
因为我们能够确认开始位置的数量并进行累加，但是没法立即确认差分的终点
不过我们可以把当下 d[i+j] 位置作为差分终点的那部分给减掉（为了抵消前面的差分）

这个时候已经不是常规的差分范围了，而是一种不同维度的差分范围

 */
// start position pairs:
// 1: (1,1)
// 2: (1,2), (2,1)

// end position pairs:
// 6: (3,3)
// 8: (3,5), (5,3)

// for 1+1 <= k <= 3+3, we need to add 1 in [2,6]
// for 1+2 <= k <= 3+5, we need to add 1 in [3,8]
// for 2+1 <= k <= 5+3, we need to add 1 in [3,8]

// all of these, can be done by following operations 
// d[i+j] += a[i]*a[j];        
// d[i+j+1] -= b[i]*b[j];
// (actually not add 1, it's multiplication by i and j)


#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
ll n,m,x,y;
int main()
{
    // freopen("3.in", "r", stdin);
    // freopen("3.out", "w", stdout);

    cin>>n>>m;
    vector<ll> a(5001,0), b(5001,0);    // a for start position, b for end position
    vector<ll> d(2*m+10, 0);            // difference array
    for(int i=0; i<n; i++){
        cin>>x>>y;
        a[x]++, b[y]++;                 // count the number of every position
    }
    for(int i=0; i<=m; i++){
        for(int j=0; j<=m; j++){
            // for multiply, we also need to use long long
            d[i+j] += a[i]*a[j];        // i+j --> ai+aj <= k, we just add a[i]*a[j] to these k
            d[i+j+1] -= b[i]*b[j];      // 这个并不是为了抵消49行的差分，而是抵消以i,j作为终点的区间
        }
    }
    ll cur = 0;
    for(int i=0; i<=2*m; i++){          // resolve the difference array
        cur += d[i];
        cout<<cur<<endl;
    }
    return 0;
}
