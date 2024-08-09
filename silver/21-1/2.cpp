// prefix + suffix

// because the empty part, we need to consider the string of two segments
// and because of the Q <= 10^5, we need a O(1) way to know the minimal number of operations
// so it's easy to think about prefix and suffix

// pre[i] is the minimal number of operations for s[0~i]
// suf[i] is the minimal number of operations for s[i~n]

// ans[i] = pre[i] + suf[i]

// and we need to consider the relation between pre[i] and pre[i-1]
// the key is to check whether there exist smaller letter in the middle of the same letter
// for exmaple: AAABAAA
// we can paint all with A, and paint B -- minimal op is 2
// but for BBBABBB, we can't! because we can only the darker color over the light color
// we can only paint BBB first, then A, then BBB -- minimal op is 3

// if there is no smaller letter in the interval, pre[i] = pre[i-1]
// it there do have smaller letter, pre[i] = pre[i-1]+1, which means we have to do a new stroke

// so the how can we quickly know whether there do have smaller letter in the interval
// there only got 26 letters, so we can use prefix sum to count the number of each letter

#include <bits/stdc++.h>
using namespace std;

int n,q;
string s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("2.in", "r", stdin);
    cin>>n>>q;
    cin>>s;

    // build prefix for letter counting
    vector<vector<int>> cnt(26);
    for(int i=0; i<n; i++){
        for(int j=0; j<26; j++){
            if(cnt[j].size() == 0) cnt[j].push_back(0);
            if(s[i]-65 == j) cnt[j].push_back(cnt[j].back()+1);
            else cnt[j].push_back(cnt[j].back());
        }
    }

    // build prefix
    vector<int> pre = {0};
    unordered_map<char,int> last;
    for(int i=0; i<26; i++) last[char(i+65)] = -1;
    for(int i=0; i<n; i++){
        if(last[s[i]] != -1){
            int flag = 0;
            for(int j=0; j<s[i]-65; j++){       // check whether there do have smaller letter between [last, i]
                if(cnt[j][i] - cnt[j][last[s[i]]] > 0) {
                    flag = 1;
                    break;
                }
            }
            if(flag) pre.push_back(pre.back() + 1);
            else pre.push_back(pre.back());
        }
        else pre.push_back(pre.back() + 1);
        last[s[i]] = i;
    }

    // build suffix
    vector<int> suf = {0};
    last.clear();
    for(int i=0; i<26; i++) last[char(i+65)] = -1;
    for(int i=n-1; i>=0; i--){
        if(last[s[i]] != -1){
            int flag = 0;
            for(int j=0; j<s[i]-65; j++){
                if(cnt[j][last[s[i]]] - cnt[j][i] > 0){
                    flag = 1;
                    break;
                }
            }
            if(flag) suf.push_back(suf.back() + 1);
            else suf.push_back(suf.back());
        }
        else suf.push_back(suf.back() + 1);
        last[s[i]] = i;
    }

    for(int i=0; i<q; i++){
        int a,b;
        cin>>a>>b;
        cout<<pre[a-1] + suf[n-b]<<'\n';
    }
    return 0;
}