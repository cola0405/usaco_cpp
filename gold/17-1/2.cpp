#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // 打开输入输出文件
    ifstream fin("hps.in");
    ofstream fout("hps.out");

    int n, k;
    fin >> n >> k;

    // 存储每次的手势
    vector<char> g(n + 1);
    for (int i = 1; i <= n; ++i) {
        fin >> g[i];
    }

    // 手势列表
    vector<char> gesture = {'P', 'H', 'S'};

    // 得分规则
    int score[3][3] = {
        {0, 1, 0},  // P: P-0, H-1, S-0
        {0, 0, 1},  // H: P-0, H-0, S-1
        {1, 0, 0}   // S: P-1, H-0, S-0
    };

    // 动态规划数组
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(k + 1, vector<int>(3, 0)));

    // 初始化第一次的得分
    for (int i = 0; i < 3; ++i) {
        int index = 0;
        if (g[1] == 'P') index = 0;
        else if (g[1] == 'H') index = 1;
        else index = 2;
        dp[1][0][i] = score[i][index];
    }

    // 动态规划过程
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            if (j > i) continue;
            for (int v = 0; v < 3; ++v) {
                int index = 0;
                if (g[i] == 'P') index = 0;
                else if (g[i] == 'H') index = 1;
                else index = 2;
                // 不变
                dp[i][j][v] = dp[i - 1][j][v] + score[v][index];
                // 变
                if (j - 1 >= 0) {
                    dp[i][j][v] = max(dp[i][j][v], max(dp[i - 1][j - 1][(v + 1) % 3], dp[i - 1][j - 1][(v + 2) % 3]) + score[v][index]);
                }
            }
        }
    }

    // 找出最大得分
    int ans = 0;
    for (int i = 0; i <= k; ++i) {
        ans = max(ans, max({dp[n][i][0], dp[n][i][1], dp[n][i][2]}));
    }

    // 输出结果
    fout << ans << endl;

    // 关闭文件
    fin.close();
    fout.close();

    return 0;
}