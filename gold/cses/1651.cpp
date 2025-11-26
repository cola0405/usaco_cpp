#include <iostream>
#include <vector>
#include <algorithm> // 用于min和max函数
using namespace std;
typedef long long ll;

vector<ll> t;
vector<int> arr;

// 构建线段树
void build(int i, int tl, int tr) {
    if (tl == tr) {
        t[i] = arr[tl];
        return;
    }
    int tm = (tl + tr) / 2;
    build(i * 2, tl, tm);
    build(i * 2 + 1, tm + 1, tr);
    // 注意：原Python代码中build未对非叶节点赋值，这里保持一致
}

// 区间更新：将[l, r]范围更新为v
void update(int i, int tl, int tr, int l, int r, ll v) {
    if (tl > r || tr < l) {
        return;
    } else if (tl == l && tr == r) {
        t[i] += v;
    } else {
        int tm = (tl + tr) / 2;
        // 递归更新左子树
        update(i * 2, tl, tm, max(l, tl), min(r, tm), v);
        // 递归更新右子树
        update(i * 2 + 1, tm + 1, tr, max(l, tm + 1), min(r, tr), v);
    }
}

// 单点查询：查询k位置的累加值（路径上所有节点值之和）
ll query(int i, int tl, int tr, int k, ll cur) {
    if (tl == tr && tl == k) {
        return cur + t[i];
    }
    cur += t[i];
    int tm = (tl + tr) / 2;
    if (k <= tm) {
        return query(i * 2, tl, tm, k, cur);
    } else {
        return query(i * 2 + 1, tm + 1, tr, k, cur);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    arr.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    // 初始化线段树，大小为4*n，初始值为0
    t.resize(4 * n, 0);
    build(1, 0, n - 1);

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) { // 更新操作：格式为1 a b v
            int a, b, v;
            cin >> a >> b >> v;
            // 转换为0-based索引
            update(1, 0, n - 1, a - 1, b - 1, v);
        } else { // 查询操作：格式为2 k
            int k;
            cin >> k;
            // 转换为0-based索引
            cout << query(1, 0, n - 1, k - 1, 0) << '\n';
        }
    }

    return 0;
}