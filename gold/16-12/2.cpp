#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int main() {
    freopen("checklist.in", "r", stdin);
    freopen("checklist.out", "w", stdout);

    int H, G;
    cin >> H >> G;

    vector<pair<int, int>> h(H+1);
    vector<pair<int, int>> g(G+1);

    for (int i = 1; i <= H; ++i) {
        cin >> h[i].first >> h[i].second;
    }
    for (int i = 1; i <= G; ++i) {
        cin >> g[i].first >> g[i].second;
    }

    int n = H + G;
    vector<vector<vector<int>>> dp(H + 1, vector<vector<int>>(G + 1, vector<int>(2, INT_MAX)));

    dp[0][0][0] = 0;
    dp[1][0][0] = 0;

    for (int i = 1; i <= H; ++i) {
        for (int j = 0; j <= G; ++j) {
            if (i-1 >= 0) {
                dp[i][j][0] = dp[i - 1][j][0] + (h[i].first - h[i-1].first) * (h[i].first - h[i-1].first) + (h[i].second - h[i-1].second) * (h[i].second - h[i-1].second);
            }
            if (j >= 1) {
                dp[i][j][0] = min(dp[i][j][0], dp[i-1][j][1] + (h[i].first - g[j].first) * (h[i].first - g[j].first) + (h[i].second - g[j].second) * (h[i].second - g[j].second));
            }

            if (j-1 >= 0) {
                dp[i][j][1] = dp[i][j - 1][1] + (g[j].first - g[j-1].first) * (g[j].first - g[j-1].first) + (g[j].second - g[j-1].second) * (g[j].second - g[j-1].second);
            }
            if (j >= 1) {
                dp[i][j][1] = min(dp[i][j][1], dp[i][j - 1][0] + (g[j].first - h[i].first) * (g[j].first - h[i].first) + (g[j].second - h[i].second) * (g[j].second - h[i].second));
            }
        }
    }

    cout << dp[H][G][0] << endl;
    return 0;
}    