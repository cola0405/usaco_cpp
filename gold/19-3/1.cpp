/*
区间dp
问题其实可以转化为 —— 最多有k个网，捕获n条连续的蛇，怎么分配区间可以尽可能减小浪费
dp[i][j] 表示到第i条蛇，且网数是j时的最小浪费
dp[i][j] = min(dp[i][j], dp[k-1][j-1] + waste)
每次往前枚举k，用新网把[k,i]之间的所有蛇抓走

因为有[k-1][j-1] 那我们需要设置初始态dp[0][0] = 0 
然后从i=1,j=1开始dp，所以需要对坐标做偏移，让index从1开始
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    freopen("snakes.in", "r", stdin);
    freopen("snakes.out", "w", stdout);

    int n, k;
    cin >> n >> k;
    vector<ll> a(n+1);
    vector<ll> pre(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pre[i] = pre[i-1] + a[i];
    }
    k++;
    vector<vector<ll>> dp(n+1, vector<ll>(k+1, LONG_MAX/2));

    /*
    初始状态无非就一种情况，就是一个网把前i个都给网了
    此时v=1,j=1, dp[v-1][j-1] = dp[0][0]
    所以我们应该把dp[0][0]设置为0
    */
    dp[0][0] = 0;

    for(int i=1; i<=n; i++){
        for(int j=1; j<=min(k, i); j++){
            ll mx = a[i];
            for(int v=i; v>=1; v--){       // 因为不知道到 dp[i][j] 用的是多大的网，所以根据 1 到 i 之间蛇的大小都试一遍（用前缀和来优化）
                mx = max(mx, a[v]);
                ll waste = mx*(i-v+1) - (pre[i]-pre[v-1]);
                dp[i][j] = min(dp[i][j], dp[v-1][j-1] + waste);
            }
        }
    }
    cout << *min_element(dp[n].begin(), dp[n].end())<<endl;
}