#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

const int mod = 1e9 + 7;

// 快速幂函数，用于计算 a^b % mod
long long fast_pow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

int main() {
    freopen("poetry.in", "r", stdin);
    freopen("poetry.out", "w", stdout);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> s(n + 1);
    vector<int> c(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> s[i] >> c[i];
    }

    vector<std::string> schema(m);
    for (int i = 0; i < m; ++i) {
        cin >> schema[i];
    }

    vector<std::vector<long long>> dp(k + 1, vector<long long>(n + 1, 0));
    vector<long long> t(k + 1, 0);
    t[0] = 1;

    for (int i = 1; i <= k; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i >= s[j]) {
                dp[i][c[j]] = (dp[i][c[j]] + t[i - s[j]]) % mod;
                t[i] = (t[i] + t[i - s[j]]) % mod;
            }
        }
    }

    unordered_map<char, int> cnt;
    for (const auto& str : schema) {
        for (char ch : str) {
            cnt[ch]++;
        }
    }

    long long ans = 1;
    for (char i = 'A'; i <= 'Z'; ++i) {
        int ch = cnt[i];
        if (ch == 0) continue;
        long long res = 0;
        for (int j = 1; j <= n; ++j) {
            res = (res + fast_pow(dp[k][j], ch)) % mod;
        }
        if (res != 0) {
            ans = (ans * res) % mod;
        }
    }

    cout << ans << endl;
    return 0;
}    