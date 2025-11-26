#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector<int> t;
vector<int> a;

// 构建线段树
void build(int i, int tl, int tr) {
    if (tl == tr) {
        t[i] = a[tl];
        return;
    }
    int tm = (tl + tr) / 2;
    build(i * 2, tl, tm);
    build(i * 2 + 1, tm + 1, tr);
    t[i] = min(t[i * 2], t[i * 2 + 1]);
}

// 查询区间最小值
int query(int i, int tl, int tr, int l, int r) {
    if (l > r) {
        return INT_MAX;
    }
    if (l == tl && r == tr) {
        return t[i];
    }
    int tm = (tl + tr) / 2;
    return min(query(i * 2, tl, tm, l, min(r, tm)),
               query(i * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // 初始化线段树数组，大小为4*n
    t.resize(4 * n, INT_MAX);
    build(1, 0, n - 1);

    while (q--) {
        int l, r;
        cin >> l >> r;
        // 转换为0-based索引
        cout << query(1, 0, n - 1, l - 1, r - 1) << '\n';
    }

    return 0;
}