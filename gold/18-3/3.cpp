#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

int main() {
    // 重定向输入输出
    ifstream fin("talent.in");
    ofstream fout("talent.out");

    int n, W;
    fin >> n >> W;

    vector<pair<int, int>> cows(n);
    for (int i = 0; i < n; ++i) {
        fin >> cows[i].first >> cows[i].second;
    }

    int max_talent = 0;
    for (const auto& cow : cows) {
        max_talent += cow.second;
    }

    vector<int> dp(max_talent + 1, INT_MAX);
    dp[0] = 0;

    for (const auto& cow : cows) {
        int weight = cow.first;
        int talent = cow.second;
        for (int i = max_talent; i >= talent; --i) {
            if (dp[i - talent] != INT_MAX && dp[i - talent] + weight < dp[i]) {
                dp[i] = dp[i - talent] + weight;
            }
        }
    }

    double max_ratio = 0.0;
    for (int t = 1; t <= max_talent; ++t) {
        if (dp[t] >= W) {
            double ratio = static_cast<double>(t) / dp[t];
            if (ratio > max_ratio) {
                max_ratio = ratio;
            }
        }
    }

    fout << static_cast<int>(max_ratio * 1000) << endl;

    fin.close();
    fout.close();

    return 0;
}    