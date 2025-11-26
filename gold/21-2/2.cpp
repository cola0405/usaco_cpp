#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<vector<int>> dp(n, vector<int>(n, 500));

    for (int i = n - 1; i >= 0; --i) {
        dp[i][i] = 1;
        for (int j = i + 1; j < n; ++j) {
            if (a[i] == a[j]) {
                dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]);
            } else {
                for (int k = i; k < j; ++k) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j]);
                }
            }
        }
    }

    cout << dp[0][n - 1] << endl;
    return 0;
} 