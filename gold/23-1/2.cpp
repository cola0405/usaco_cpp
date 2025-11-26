#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n;
vector<vector<bool>> dp; // 使用 bool 节省空间

// 将二进制字符串转换为整数（如 "101" -> 5）
int bin_to_int(const string& s) {
    int res = 0;
    for (char c : s) {
        res = (res << 1) | (c - '0');
    }
    return res;
}

// 翻转从 start 开始、长度为 len 的连续位（允许环绕）
int get_state(int s, int start, int length) {
    int r = start + length - 1;

    // Part 1: non-wrapped segment [start, min(r, n-1)]
    int right_end = (r < n) ? r : n - 1;
    int r_len = right_end - start + 1;
    if (r_len > 0) {
        int shift = n - 1 - start - (r_len - 1); // = n - start - r_len
        int mask = ((1 << r_len) - 1) << shift;
        s ^= mask;
    }

    // Part 2: wrapped segment at the beginning (if any)
    if (r >= n) {
        int l_len = r - (n - 1); // number of bits wrapped to the front
        int shift = n - 1 - (l_len - 1); // = n - l_len
        int mask = ((1 << l_len) - 1) << shift;
        s ^= mask;
    }

    return s;
}

// 向右旋转：最低位移到最高位（对应题目中 rotate 操作）
// 例如 n=4, 0b1101 -> 0b1110 （原最低位 1 移到最高位）
int rotate_right(int x) {
    if (n == 0) return 0;
    int low_bit = x & 1;
    return (x >> 1) | (low_bit << (n - 1));
}

void init() {
    dp.assign(n + 2, vector<bool>(1 << n, false));
    dp[0][0] = true;

    for (int i = 0; i <= n; ++i) {
        for (int st = 0; st < (1 << n); ++st) {
            if (dp[i][st]) {
                for (int j = 0; j < n; ++j) {
                    int next_state = get_state(st, j, i + 1);
                    dp[i + 1][next_state] = true;
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t >> n;

    init();

    while (t--) {
        string a, b;
        cin >> a >> b;
        int s1 = bin_to_int(a);
        int s2 = bin_to_int(b);

        int ans = -1;
        for (int k = 0; k <= n; ++k) {
            if (dp[k][s1]) {
                ans = k;
                break;
            }
            s1 ^= s2;
            s2 = rotate_right(s2);
        }

        cout << ans << '\n';
    }

    return 0;
}