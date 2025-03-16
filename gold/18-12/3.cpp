/*
DP + 线段树
Python 拿不了满分

经典的线性DP问题
其实是最多K个连续中取最大值，又 K<=1000 比较小, 则可以把所有可能都试一遍 —— 往前连1个、2个、... 、k个
但是加上求区间最大值时间复杂度为O(NK^2)
然后用线段树优化区间最大值问题，把复杂度降到O(NK*LogN)即可
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
typedef long long ll;

// 线段树类
class SegmentTree {
private:
    int n;
    vector<int> tree;

    // 递归构建线段树
    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            int left = 2 * node + 1;
            int right = 2 * node + 2;
            build(arr, left, start, mid);
            build(arr, right, mid + 1, end);
            tree[node] = max(tree[left], tree[right]);
        }
    }

    // 查询 (l, r) 区间的最大值
    int query(int node, int start, int end, int l, int r) {
        if (r < start || l > end) {
            return INT_MIN;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int left = 2 * node + 1;
        int right = 2 * node + 2;
        return max(query(left, start, mid, l, r), query(right, mid + 1, end, l, r));
    }

public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n, 0);
        build(arr, 0, 0, n - 1);
    }

    // 调用 query 函数查询最大值
    int max_value(int l, int r) {       // 不能叫max 不然命名会冲突
        return query(0, 0, n - 1, l, r);
    }
};

int main() {
    ifstream fin("teamwork.in");
    ofstream fout("teamwork.out");

    int n, k;
    fin >> n >> k;

    vector<int> s(n);
    for (int i = 0; i < n; ++i) {
        fin >> s[i];
    }

    if (n == 1) {
        fout << s[0] << endl;
        return 0;
    }

    vector<ll> dp(n + 1, 0);    // dp[i] 表示以i结尾的最优解（可能连前面也可能没连）
    dp[1] = s[0];
    dp[2] = max(s[0], s[1]) * 2;

    SegmentTree seg(s);

    for (int i = 2; i < n; ++i) {
        for (int j = 0; j < k; ++j) {   // 对于s[i], 我只需要往前考虑是否连K位即可
            if (i - j < 0) continue;
            // s[i]对应的dp位在dp[i+1],要留出dp[0]来做dp
            dp[i + 1] = max(dp[i + 1], dp[i - j] + seg.max_value(i - j, i) * (j + 1));
        }
    }

    fout << dp[n] << endl;

    fin.close();
    fout.close();

    return 0;
}