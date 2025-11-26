// https://www.doubao.com/chat/2976955563233026

#include<bits/stdc++.h>
using namespace std;
// 定义长整型别名，方便处理可能较大的结果
typedef long long ll;
// 定义整数对别名，用于存储询问和其原始顺序
typedef pair<int,int> pii;

// 计算三个数的中位数
inline int median(int x,int y,int z){
    // 三个数的和减去最大值和最小值即为中位数
    return x + y + z - max({x, y, z}) - min({x, y, z});
}

int main(){
    // 优化输入输出流，提高效率
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, l1 = 0, l2 = 0;
    // 读取节点数量
    cin >> n;

    // 存储每个节点的初始值
    vector<int> a(n + 1);
    // 存储每个节点修改值的花费
    vector<int> c(n + 1);
    // 读取每个节点的初始值和修改花费
    for(int i = 1; i <= n; i++)
        cin >> a[i] >> c[i];

    // 存储节点编号，用于后续按初始值排序
    vector<int> ps(n);
    // 初始化节点编号为 1 到 n
    iota(ps.begin(), ps.end(), 1);
    // 按节点的初始值从小到大排序
    sort(ps.begin(), ps.end(), [&](int x, int y){
        return a[x] < a[y];
    });

    // 二维向量 f 用于存储动态规划的状态
    // f[u][0] 表示节点 u 经过操作后值小于目标值的最小花费
    // f[u][1] 表示节点 u 经过操作后值等于目标值的最小花费
    // f[u][2] 表示节点 u 经过操作后值大于目标值的最小花费
    vector f(n + 1, vector<ll>(3, 1e18));

    int q;
    // 读取询问的数量
    cin >> q;

    // 定义更新函数，用于更新节点 u 的动态规划状态
    auto upd = [&](int u, int m){
        // 初始化节点 u 的状态为一个很大的值
        f[u] = vector<ll>(3, 1e18);
        // 存储修改节点 u 值的花费
        vector<ll> w(3);

        // 根据节点 u 的初始值和目标值 m 的大小关系，计算修改花费
        if(a[u] < m) w[1] = w[2] = c[u];
        else if(a[u] == m) w[0] = w[2] = c[u];
        else w[0] = w[1] = c[u];

        // 如果节点 u 有两个子节点
        if((u << 1 | 1) <= n){
            // 枚举子节点和当前节点的三种状态
            for(int i = 0; i < 3; i++)
                for(int j = 0; j < 3; j++)
                    for(int k = 0; k < 3; k++){
                        // 计算三个状态的中位数
                        int med = median(i, j, k);
                        // 更新节点 u 的中位数状态的最小花费
                        f[u][med] = min(f[u][med], f[u << 1][i] + f[u << 1 | 1][j] + w[k]);
                    }
        }
        // 如果节点 u 没有子节点，直接将 w 赋值给 f[u]
        else f[u] = w;
    };

    // 定义更新祖先节点的函数
    auto g = [&](int x, int m){
        // 从节点 x 开始，依次更新其所有祖先节点的状态
        for(int i = 0; x >> i; i++)
            upd(x >> i, m);
    };

    // 存储询问和询问的原始顺序
    vector<pii> Q(q);
    // 读取每个询问的目标值，并记录其原始顺序
    for(int i = 0; i < q; i++)
        cin >> Q[i].first, Q[i].second = i;

    // 存储每个询问的结果
    vector<ll> R(q);
    // 按询问的目标值从小到大排序
    sort(Q.begin(), Q.end());

    // 初始化所有节点的状态，目标值设为 0
    for(int i = n; i; i--)
        g(i, 0);

    // 离线处理每个询问
    for(auto [m, p] : Q){
        // 当节点的初始值小于目标值 m 时，更新该节点及其祖先的状态
        while(l1 < n && a[ps[l1]] < m) g(ps[l1++], m);
        // 当节点的初始值小于等于目标值 m 时，更新该节点及其祖先的状态
        while(l2 < n && a[ps[l2]] <= m) g(ps[l2++], m);
        // 记录根节点等于目标值 m 的最小花费
        R[p] = f[1][1];
    }

    // 按原始询问顺序输出每个询问的结果
    for(ll i : R) cout << i << '\n';

    return 0;
}