#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>
using namespace std;

const int MOD = 1e9 + 7;

// 线段树构建函数
void build(int i, int tl, int tr, const vector<long long>& dp, vector<long long>& t) {
    if (tl == tr) {
        t[i] = dp[tl];
        return;
    }
    int tm = (tl + tr) / 2;
    build(i * 2, tl, tm, dp, t);
    build(i * 2 + 1, tm + 1, tr, dp, t);
    t[i] = (t[i * 2] + t[i * 2 + 1]) % MOD;
}

// 线段树查询函数
long long query(int i, int tl, int tr, int l, int r, const vector<long long>& t) {
    if (l > r) return 0;
    if (l == tl && r == tr) return t[i];
    int tm = (tl + tr) / 2;
    return (query(i * 2, tl, tm, l, min(r, tm), t) + 
            query(i * 2 + 1, tm + 1, tr, max(l, tm + 1), r, t)) % MOD;
}

// 线段树更新函数
void update(int i, int tl, int tr, int pos, long long new_val, vector<long long>& t) {
    if (tl == tr) {
        t[i] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) {
            update(i * 2, tl, tm, pos, new_val, t);
        } else {
            update(i * 2 + 1, tm + 1, tr, pos, new_val, t);
        }
        t[i] = (t[i * 2] + t[i * 2 + 1]) % MOD;
    }
}

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = " " + s;  // 使字符串索引从1开始，与Python代码保持一致
    
    // 初始化线段树，大小为4*(n+1)以确保足够空间
    vector<long long> t_even(4 * (n + 1), 0);
    vector<long long> t_odd(4 * (n + 1), 0);
    
    // 优先队列（小根堆），存储(值, 索引)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    vector<long long> dp(n + 1, 0);
    dp[0] = 1;
    
    // 初始化线段树
    update(1, 0, n, 0, 1, t_even);
    
    int red = 0;
    vector<int> blue(n + 2, 0);  // blue[i]表示i之后的第一个B的位置
    int b = n + 1;
    
    // 预处理blue数组
    for (int i = n; i >= 0; --i) {
        blue[i] = b;
        if (s[i] == 'B') {
            b = i;
        }
    }
    
    pq.push({2 * blue[0] - 1, 0});
    
    for (int i = 1; i <= n; ++i) {
        // 删除非法节点
        while (!pq.empty() && i > pq.top().first) {
            int k = pq.top().second;
            pq.pop();
            if (k % 2 == 0) {
                update(1, 0, n, k, 0, t_even);
            } else {
                update(1, 0, n, k, 0, t_odd);
            }
        }
        
        if (s[i] == 'R') {
            red = i;
        } else {
            if (s[i] == 'X') {
                dp[i] = dp[i - 1];
            }
            
            if (i % 2 == 0) {
                int left = max(2 * red - i, 0);
                dp[i] = (dp[i] + query(1, 0, n, left, i - 1, t_even)) % MOD;
                update(1, 0, n, i, dp[i], t_even);
            } else {
                int left = max(2 * red - i, 0);
                dp[i] = (dp[i] + query(1, 0, n, left, i - 1, t_odd)) % MOD;
                update(1, 0, n, i, dp[i], t_odd);
            }
        }
        
        // 将当前节点加入优先队列
        pq.push({2 * blue[i] - i - 2, i});
    }
    
    cout << dp[n] % MOD << endl;
    
    return 0;
}
