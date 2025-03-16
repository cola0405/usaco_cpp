/* 最后一个点usaco超时*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("snakes.in", "r", stdin);
    freopen("snakes.out", "w", stdout);

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin>>a[i];

    unordered_set<int> s(a.begin(), a.end());
    vector<vector<unordered_map<int, ll>>> dp(2, vector<unordered_map<int, ll>>(k+1));
    vector<vector<long long>> min_val(2, vector<long long>(k + 1, LLONG_MAX));
    
    // 初始化第一行
    min_val[0][0] = 0;
    for (int v : s) dp[0][0][v] = LLONG_MAX;
    for (int ai : s) {
        if (ai >= a[0]) {
            dp[0][0][ai] = ai - a[0];
        }
    }

    for (int i = 1; i < n; ++i) {
        int cur = i & 1, prev = (i-1) & 1;
        // 清空当前行
        for (int j = 0; j <= k; ++j) {
            min_val[cur][j] = LLONG_MAX;
            for (int v : s) dp[cur][j][v] = LLONG_MAX;
        }

        for (int j = 0; j <= min(k, i + 1); ++j) {
            for (int v : s) {
                if(v < a[i]) continue;
                // 不变的情况
                if (dp[prev][j][v] != LLONG_MAX){
                    dp[cur][j][v] = min(dp[cur][j][v], dp[prev][j][v] + (v - a[i]));
                }
                
                // 变为v的情况
                if(j > 0 && min_val[prev][j-1] != LLONG_MAX){
                    dp[cur][j][v] = min(dp[cur][j][v], min_val[prev][j-1] + (v - a[i]));
                }
                // 更新min_val
                if (dp[cur][j][v] < min_val[cur][j]) {
                    min_val[cur][j] = dp[cur][j][v];
                }
            }
        }
    }
    cout << *min_element(min_val[(n-1)&1].begin(), min_val[(n-1)&1].end()) << endl;
    return 0;
}