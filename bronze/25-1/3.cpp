#include <iostream>
#include <vector>

using namespace std;

// 定义全局变量
int l, r, cnt;
vector<int> a, b;
vector<int> ans;

// 扩展函数
void expand() {
    l--;
    r++;
    // 逆序，则认为 l到 r位置，r到 l位置
    // 后面减法是减去逆序前的数量
    cnt += (a[l] == b[r]) + (a[r] == b[l]) - (a[l] == b[l]) - (a[r] == b[r]);
    ans[cnt]++;
}

int main() {
    int n;
    cin >> n;
    a.resize(n);
    b.resize(n);
    ans.resize(n + 1, 0);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    int fit = 0;
    for (int i = 0; i < n; i++) if (a[i] == b[i]) fit++;

    for (int i = 0; i < n; i++) {
        cnt = fit;
        l = i + 1;
        r = i - 1;
        while (l - 1 >= 0 && r + 1 < n) expand();
    }

    for (int i = 0; i < n; i++) {      
        cnt = fit;
        l = i + 1;              // 处理偶数长度的逆序（上面只处理了奇数长度序列）
        r = i;
        while (l - 1 >= 0 && r + 1 < n) expand();
    }

    for (int x : ans) cout << x << endl;
    return 0;
}