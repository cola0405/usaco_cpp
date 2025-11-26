#include <bits/stdc++.h>
using namespace std;

int n, Q;
vector<long long> h;
vector<set<int>> s; // 对应 SortedSet
long long ans = 0;

// 计算 (i,j) 的斜率, j > i
double cal(int i, int j) {
    return (double)(h[j] - h[i]) / (j - i);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    h.resize(n + 1);
    for (int i = 1; i <= n; ++i) cin >> h[i];

    s.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        s[i].insert(0);
        s[i].insert(n + 1);

        int mx = i + 1;
        for (int j = i + 1; j <= n; ++j) {
            if (cal(i, mx) <= cal(i, j)) {
                s[i].insert(j);
                ans += 1;
                if (h[j] > h[mx]) mx = j;
            }
        }
    }

    cin >> Q;
    while (Q--) {
        int x, d;
        cin >> x >> d;
        h[x] += d;

        for (int i = 1; i < x; ++i) {
            auto it = s[i].lower_bound(x);
            int left = *(--it); // 左边的元素
            if (left > i && cal(i, left) > cal(i, x)) continue;

            if (s[i].count(x) == 0) {
                s[i].insert(x);
                ans += 1;
            }

            it = s[i].upper_bound(x);
            while (it != s[i].end() && *it <= n) {
                int right = *it;
                if (cal(i, right) >= cal(i, x)) break;
                it = s[i].erase(it);
                ans -= 1;
            }
        }

        // rebuild s[x]
        ans -= s[x].size() - 2; // 减去 0 和 n+1 哨兵
        s[x].clear();
        s[x].insert(0);
        s[x].insert(n + 1);

        double mx_slope = -1e18;
        for (int i = x + 1; i <= n; ++i) {
            if (cal(x, i) >= mx_slope) {
                s[x].insert(i);
                ans += 1;
                mx_slope = max(mx_slope, cal(x, i));
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
