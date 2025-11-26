#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

using ll = long long;

int n;
vector<ll> a;
vector<int> L, R;
vector<ll> p, s;

void add(int l, int r, ll h, ll d) {
    if (r < l) return;
    p[l] += h;
    p[r + 1] -= d * (r - l) + h;
    s[l + 1] += d;
    s[r + 1] -= d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    a.resize(3 * n + 1); // 1-based indexing
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = n + 1; i <= 3 * n; ++i) {
        a[i] = a[i - n]; // repeat
    }

    L.assign(3 * n + 1, 0);
    R.assign(3 * n + 1, 0);

    // 左边第一个比a[i]小的
    stack<int> st;
    for (int i = 1; i <= 3 * n; ++i) {
        while (!st.empty() && a[st.top()] >= a[i]) {
            st.pop();
        }
        if (!st.empty()) L[i] = st.top();
        st.push(i);
    }

    // 右边第一个比a[i]小的
    while (!st.empty()) st.pop();
    for (int i = 3 * n; i >= 1; --i) {
        while (!st.empty() && a[st.top()] > a[i]) {
            st.pop();
        }
        if (!st.empty()) R[i] = st.top();
        st.push(i);
    }

    p.assign(2 * n + 2, 0);
    s.assign(2 * n + 2, 0);

    for (int i = 1; i <= n; ++i) {
        int li = max(L[i + n], i) - n;
        int ri = min(R[i + n], i + 2 * n) - n;
        int left = i - li;
        int right = ri - i;

        int min_lr = min(left, right);
        int max_lr = max(left, right);
        int sum_lr = left + right;

        add(1, min_lr, a[i], a[i]);
        add(min_lr + 1, max_lr, 1LL * min_lr * a[i], 0);
        add(max_lr + 1, sum_lr, 1LL * min_lr * a[i] - a[i], -a[i]);
    }

    // 还原二阶差分
    for (int i = 1; i <= n; ++i) {
        s[i] += s[i - 1];
        p[i] += s[i];
    }
    for (int i = 2; i <= n; ++i) {
        p[i] += p[i - 1];
        cout << p[i] << '\n';
    }
    cout << p[n] << '\n';

    return 0;
}
