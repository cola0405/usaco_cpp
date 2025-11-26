#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n, vector<int>(n, 1));
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a][b] = g[b][a] = 0;
    }

    vector<int> a(1 << n, 0);
    for (int S = 1; S < (1 << n); ++S) {
        for (int i = 0; i < n; ++i) {
            if (S & (1 << i)) {
                for (int j = 0; j < n; ++j) {
                    if (i == j) continue;
                    if ((S & (1 << j)) && g[i][j] == 0) a[S]++;
                    else if (!(S & (1 << j)) && g[i][j]) a[S]++;
                }
            }
        }
    }

    vector<int> dp(1 << n, 0);
    dp[0] = 0;
    for (int S = 1; S < (1 << n); ++S) {
        dp[S] = a[S];
        int s = S;
        while (s) {
            dp[S] = min(dp[S], dp[S ^ s] + a[s]);
            s = (s - 1) & S;
        }
    }

    cout << dp[(1 << n) - 1] / 2 << endl;

    return 0;
}    