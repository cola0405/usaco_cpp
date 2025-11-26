#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL INF = 1e18;     // 防止子树大小溢出
const int N = 200105;    // Σ|s| 最大 2e5，所以点数开到 2e5 级别

// 结点结构：存放字符、左右孩子、子树大小
struct Node {
    char v;   // 如果是叶子，存 'a'..'z'；如果是拼接结点，存 '#'
    int lc, rc; // 左右孩子下标
    LL sz;   // 子树大小，超过 1e18 就截断
} tr[N];

int root[26], ck; // root[c] 存放字符 c 的最终树根节点编号
char c[N];        // 存储每条规则的被替换字符
string s[N];      // 存储每条规则的替换串

// 区间查询函数：输出 [l, r] 的字符串
void query(int u, LL l, LL r) {
    if (r <= 0 || l > tr[u].sz) return;  // 当前结点区间与 [l,r] 无交集，直接返回
    if (tr[u].v == '#') {
        // 如果是拼接结点，递归到左右子树
        query(tr[u].lc, l, r);  // 左子树负责 [l, r] 的一部分
        // 注意右子树的区间要平移，减去左子树大小
        query(tr[u].rc, l - tr[tr[u].lc].sz, r - tr[tr[u].lc].sz);
    } else {
        // 如果是叶子结点（具体字母），直接输出
        putchar(tr[u].v);
    }
}

int main() {
    LL l, r, n;
    cin >> l >> r >> n;

    // 读入 n 条替换规则
    for (int i = 1; i <= n; i++) cin >> c[i] >> s[i];

    // 初始化：每个字母一颗单点叶子树
    for (int i = 0; i < 26; i++) {
        tr[++ck] = {char('a' + i), 0, 0, 1};
        root[i] = ck;
    }

    // 倒序处理替换规则
    for (int i = n; i >= 1; i--) {
        int now = 0;  // 当前拼接结果的根
        for (auto x : s[i]) {
            x -= 'a';   // 字母转索引
            if (now == 0) {
                // 第一个字符：直接拿它的树
                now = root[x];
            } else {
                // 后续字符：与已有拼接结果合并成新结点
                tr[++ck] = {
                    '#',      // 新结点是拼接结点
                    now,      // 左子树是已有部分
                    root[x],  // 右子树是当前字符的树
                    min(INF, tr[now].sz + tr[root[x]].sz)  // 子树大小
                };
                now = ck;  // 更新拼接结果的根
            }
        }
        // 更新被替换字符的根节点
        root[c[i] - 'a'] = now;
    }

    // 最终字符串是从 root['a'] 展开的，查询 [l, r]
    query(root[0], l, r);
    putchar('\n');
    return 0;
}
