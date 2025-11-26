#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;  // 需要比 n 大一些
int n;
int c[MAXN];
long long diff[MAXN];  // 用 long long 防止组数溢出
vector<int> pos[MAXN]; // 每个颜色出现的位置

// 计算某个 color 在给定间隔 x 下的组数
int cal(int x, int color) {
    int res = 0;
    int last = -1000000000; // -inf
    for (int p : pos[color]) {
        if (p - last > x) {
            res++;
            last = p;
        }
    }
    return res;
}

// 差分更新 [l, r] 加 v
void update(int l, int r, int v) {
    if (l > r) return;
    diff[l] += v;
    if (r + 1 <= n) diff[r + 1] -= v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        pos[c[i]].push_back(i);
    }

    int B = sqrt(n);

    // 当 x <= B 时，暴力处理
    for (int x = 1; x <= B; x++) {
        for (int color = 1; color <= n; color++) {
            if (!pos[color].empty()) {
                update(x, x, cal(x, color));
            }
        }
    }

    // 当 x > B 时，二分处理
    for (int color = 1; color <= n; color++) {
        if (pos[color].empty()) continue;
        int cur = B + 1;
        while (cur <= n) {
            int cur_group = cal(cur, color);
            int L = cur, R = n;
            while (L < R) {
                int mid = (L + R + 1) / 2;
                if (cal(mid, color) == cur_group) {
                    L = mid;
                } else {
                    R = mid - 1;
                }
            }
            update(cur, L, cur_group);
            cur = L + 1;
        }
    }

    long long res = 0;
    for (int i = 1; i <= n; i++) {
        res += diff[i];
        cout << res << "\n";
    }

    return 0;
}
