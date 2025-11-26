#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; ++i) {
        cin >> a[i];
    }
    ll max_a = *max_element(a.begin(), a.end());
    vector<ll> cnt1(max_a + 1, 0);
    for (ll x : a) {
        cnt1[x]++;
    }
    for (ll i = 1; i <= max_a; ++i) {
        cnt1[i] += cnt1[i - 1];
    }
    vector<ll> cnt2(max_a + 1, 0);
    ll ans = 0;
    for (ll s = 1; s <= max_a; ++s) {
        ll max_t = max_a / s;
        for (ll i = 1; i <= max_t; ++i) {
            cnt2[i] = cnt1[min(s * (i + 1) - 1, max_a)] - cnt1[s * i - 1];
        }
        ll odd_cnt = 0;
        for (ll i = 1; i <= max_t; ++i) {
            if (cnt2[i] % 2 == 1) {
                odd_cnt++;
            }
        }
        if (odd_cnt == 1 && cnt2[1] % 2 == 1) {
            ans += cnt2[1];
        }
        if (odd_cnt == 2) {
            for (ll i = 2; i <= max_t; ++i) {
                if (cnt2[i] % 2 == 1 && cnt2[i - 1] % 2 == 1) {
                    ans += cnt2[i];
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}    