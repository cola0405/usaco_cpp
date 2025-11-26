#include <bits/stdc++.h>
using namespace std;

struct Subarray {
    long long sum;
    int l, r;
    bool operator<(const Subarray& other) const {
        if (sum == other.sum) return l < other.l;
        return sum < other.sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n + 1), pre(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];

    // 前缀和
    for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + a[i];

    // 枚举所有子数组
    vector<Subarray> s;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            s.push_back({pre[j] - pre[i - 1], i, j});
        }
    }

    sort(s.begin(), s.end());

    // 对每个位置 i，找最小差值
    for (int i = 1; i <= n; i++) {
        long long ans = LLONG_MAX;
        for (int j = 0; j + 1 < (int)s.size(); j++) {
            auto [v1, l1, r1] = s[j];
            auto [v2, l2, r2] = s[j + 1];
            bool cover1 = (l1 <= i && i <= r1);
            bool cover2 = (l2 <= i && i <= r2);
            if (cover1 ^ cover2) { // 恰好一个区间包含 i
                ans = min(ans, llabs(v1 - v2));
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
