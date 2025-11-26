#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

int main() {
    int n;
    cin >> n;
    
    vector<int> h(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> h[i];
    }
    
    // dp[i][j] 表示前 i 头牛，第 i 头牛饥饿水平为 j 时的方案数
    vector<vector<int>> dp(n + 1, vector<int>(1001, 0));
    
    int mn = *min_element(h.begin() + 1, h.begin() + n + 1);
    if (n % 2 == 0) {
        mn = 0;  // 如果 n 为偶数，不需要偏移量
    }
    
    // 初始化第一头牛的状态
    for (int j = 0; j <= h[1]; ++j) {
        dp[1][j] = j + 1;  // 前缀和累加
    }
    
    int ans = 0;
    for (int d = 0; d <= mn; ++d) {  // 枚举偏移量 d
        for (int i = 2; i <= n; ++i) {  // 遍历处理每一头牛
            
            // 计算上一层可转移的最后一项
            int last = min(h[i], h[i-1]) - d;
            dp[i][0] = dp[i-1][last];
            
            // 当前牛可能的最大饥饿水平
            int max_j = h[i] - d;
            for (int j = 1; j <= max_j; ++j) {  // 枚举当前牛的饥饿水平 j
                
                // 计算上一层可转移的最后一项
                last = min(h[i] - j, h[i-1]) - d;
                dp[i][j] = (dp[i][j-1] + dp[i-1][last]) % MOD;
            }
        }
        
        // 累加不同偏移量下的结果
        ans = (ans + dp[n][0]) % MOD;
    }
    
    cout << ans << endl;
    
    return 0;
}