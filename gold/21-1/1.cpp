#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>
#include <set>
#include <unordered_map>

using namespace std;

int main() {
    string s;
    cin >> s;

    // 找出字符串中存在的不同字母
    set<char> uniqueChars(s.begin(), s.end());
    vector<char> al(uniqueChars.begin(), uniqueChars.end());

    int n = s.length();
    int m = al.size();

    // 统计相邻字母的出现次数
    unordered_map<char, unordered_map<char, int>> cnt;
    for (int i = 0; i < n - 1; ++i) {
        cnt[s[i]][s[i + 1]]++;
    }

    // 初始化动态规划数组
    vector<int> dp(1 << m, INT_MAX);
    dp[0] = 1;

    // 枚举所有状态 S
    for (int S = 1; S < (1 << m); ++S) {
        // 枚举可能转移到 dp[S] 的状态
        for (int i = 0; i < m; ++i) {
            if (S & (1 << i)) {
                int tot = dp[S ^ (1 << i)];
                // 枚举每个字母，计算重复唱的次数
                for (int j = 0; j < m; ++j) {
                    if (S & (1 << j)) {
                        tot += cnt[al[i]][al[j]];
                    }
                }
                dp[S] = min(dp[S], tot);
            }
        }
    }

    // 输出结果
    cout << dp.back() << endl;

    return 0;
}