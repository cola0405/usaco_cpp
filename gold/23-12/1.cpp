#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> p(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> g(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i < n; ++i) {
        string line;
        cin >> line;
        for (int j = 0; j < line.length(); ++j) {
            p[i][i + j + 1] = line[j] - '0';
        }
    }

    int ans = 0;
    for (int i = n; i >= 1; --i) {
        for (int j = i + 1; j <= n; ++j) {
            int cnt = 0;
            for (int k = i + 1; k < j; ++k) {
                if (g[i][k]) {
                    cnt ^= p[k][j];
                }
            }
            if (cnt != p[i][j]) {
                g[i][j] = 1;
                ans++;
            }
        }
    }

    cout << ans << endl;

    return 0;
}