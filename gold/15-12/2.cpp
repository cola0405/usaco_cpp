#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("feast.in", "r", stdin);
    freopen("feast.out", "w", stdout);

    int t, a, b;
    cin >> t >> a >> b;

    vector<bool> dp = vector<bool>(t + 1, false);
    dp[0] = true;
    for(int i=a; i <= t; i++) dp[i] = dp[i] | dp[i - a];
    for(int i=b; i <= t; i++) dp[i] = dp[i] | dp[i - b];
    for(int i=1; i <= t; i++) dp[i/2] = dp[i/2] | dp[i];
    for(int i=a; i <= t; i++) dp[i] = dp[i] | dp[i - a];
    for(int i=b; i <= t; i++) dp[i] = dp[i] | dp[i - b];
    while (t) {
        if (dp[t]) {
            cout << t << endl;
            break;
        }
        t--;
    }
    return 0;
}    