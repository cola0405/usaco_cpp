#include <iostream>
#include <vector>
#include <climits>
#include <algorithm> // 用于min和max函数
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

// 更新线段树
void update(int i, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t[i] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) {
            update(i * 2, tl, tm, pos, new_val);
        } else {
            update(i * 2 + 1, tm + 1, tr, pos, new_val);
        }
        t[i] = min(t[i * 2], t[i * 2 + 1]);
    }
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

    // 初始化线段树，大小为4*n，初始值为INT_MAX
    t.resize(4 * n, INT_MAX);
    build(1, 0, n - 1);

    while (q--) {
        int typ, a_val, b_val;
        cin >> typ >> a_val >> b_val;
        if (typ == 1) {
            // 更新操作：a_val是1-based位置，转换为0-based
            update(1, 0, n - 1, a_val - 1, b_val);
        } else {
            // 查询操作：a_val和b_val是1-based范围，转换为0-based
            cout << query(1, 0, n - 1, a_val - 1, b_val - 1) << '\n';
        }
    }

    return 0;
}