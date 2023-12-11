// 连通分量(并查集) + 二分 + 优先级队列

// 把首末barn 当作是两个连通分量
// 我们的任务就是尝试找到一个中转的连通分量，建立通路，使得首末相接 (最多搭两条路)
// 问题的关键在于怎么更高效的找到那两条路,双重循环暴力会超时 (只能过部分测试用例)
// 解决办法是 O(n) 遍历所有节点，然后通过二分找到当前节点到首、末的最短路
// 将其分别放入当前连通分量的 left 和 right 优先级队列中
// 最后只要遍历所有连通分量，找 left+right 的最小值即可

// 观察太极的图案
// 不一定是min与max
// N=10 连通分量(1,5,6) 和 (4,10), 此时 "4-5" 是最佳选择，与min max 都无关
// 那怎么找两个连通分量之间的最短路呢
// 二分：一个节点到某连通分量的最短路肯定在 lower_bound 或 upper_bound

// 可能是中间连通分量中的两个node分别作连接
// 还有要注意的就是，虽然题目没说，但是 cost 需要用到 long long

#include<bits/stdc++.h>
using namespace std;

int N,M;
vector<int> u;
unordered_map<int, vector<int>> components;
int find(int x){
    if(x == u[x]) return x;
    u[x] = find(u[x]);
    return u[x];
}

long long getCost(int a, long long b){   // 最近点可以通过lower upper bound 来找，要注意的是锁定insert place 后具体取哪个还得筛选
    if(find(a) == find(b)) return 0;
    vector<int>& nodes = components[find(a)];
    int upper = upper_bound(nodes.begin(), nodes.end(), b) - nodes.begin();
    int lower = lower_bound(nodes.begin(), nodes.end(), b) - nodes.begin();
    vector<long long> res;  // lower_bound 只能找到适合的插入位置，但是无法立即确认到底是离左边近还是右边
    if(lower-1>=0 && lower-1<nodes.size()) res.push_back(pow(nodes[lower-1]-b, 2));
    if(upper-1>=0 && upper-1<nodes.size()) res.push_back(pow(nodes[upper-1]-b, 2));
    if(lower>=0 && lower<nodes.size()) res.push_back(pow(nodes[lower]-b, 2));
    if(upper>=0 && upper<nodes.size()) res.push_back(pow(nodes[upper]-b, 2));
    return *min_element(res.begin(), res.end());
}

int main(){
    // freopen("2.in", "r", stdin);
    // freopen("2.out", "w", stdout);

    int T;
    cin>>T;
    for(int y=0; y<T; y++){
        cin>>N>>M;

        // build disjoint-set
        u.clear();
        for(int i=0; i<=N; i++) u.push_back(i);
        for(int i=0; i<M; i++){
            int a,b;
            cin>>a>>b;
            u[find(b)] = u[find(a)];
        }

        // build components
        components.clear();
        for(int i=1; i<=N; i++){
            components[find(i)].push_back(i);
        }

        // 优先级队列用来保存某连通分量到达首、末的最短路, 首-left，末-right
        unordered_map<int, priority_queue<long long, vector<long long>, greater<long long>>> left, right;
        for(int mid=1; mid<=N; mid++){   // 尝试所有中转的节点，二分找到最短路，然后记录起来
            long long c1 = getCost(1, mid);
            long long c2 = getCost(N, mid);
            left[find(mid)].push(c1);
            right[find(mid)].push(c2);
        }

        long long cost = LONG_LONG_MAX;
        for(auto x: components){    // 遍历所有的连通分量，查找到首、末的最小花费
            long long c1 = left[x.first].top();     // 到首的最小花费
            long long c2 = right[x.first].top();    // 末
            cost = min(cost, c1+c2);
        }
        cout<<cost<<endl;
    }
}