// not done yet
#include <bits/stdc++.h>
using namespace std;

int T, C, t, pos=0, x;
string c;
unordered_map<int, int> cnt;                // the hit cnt of each target
vector<int> target(2e5 + 100, 0);
vector<unordered_set<int>> suf(5);           // record the hit targets of suffix for 5 offset
int main()
{
    freopen("3.in", "r", stdin);
    freopen("3.out", "w", stdout);

    ios::sync_with_stdio(false);
    cin>>T>>C;
    for(int i=0; i<T; i++){
        cin>>x;
        target[x+100000] = 1;
    }
    cin>>c;
    vector<int> pre;                  // 0~(i-1) will not be affected, so we can build prefix
    pre.reserve(C+1);
    pre.push_back(0);
    for(int i=0; i<C; i++){
        if(c[i] == 'L') pos--;
        if(c[i] == 'R') pos++;
        if(c[i] == 'F') {
            if(target[pos+100000] && cnt[pos] == 0) pre.push_back(pre.back() + 1);
            else pre.push_back(pre.back());
            cnt[pos]++;     // only record the cnt when offset=0
        } else pre.push_back(pre.back());
    }
    int ans = pre.back();      // no change
    for(int i=C-1; i>=0; i--){
        if(c[i] == 'L'){
            pos++;
            // to R
            int cnt1 = pre[i] + suf[2+2].size();
            ans = max(ans, cnt1);

            // to F
            int cnt2 = pre[i] + suf[1+2].size();
            if(target[pos+100000] && suf[1+2].find(pos) == suf[1+2].end() && cnt[pos] == 0) cnt2++;
            ans = max(ans, cnt2);
        }
        else if(c[i] == 'R'){
            pos--;
            // to L
            int cnt1 = pre[i] + suf[-2+2].size();
            ans = max(ans, cnt1);

            // to F
            int cnt2 = pre[i] + suf[-1+2].size();
            if(target[pos+100000] && suf[-1+2].find(pos) == suf[-1+2].end() && cnt[pos] == 0) cnt2++;
            ans = max(ans, cnt2);
        }
        else{
            // to L
            int cnt1 = pre[i] + suf[-1+2].size();
            ans = max(ans, cnt1);

            // to R
            int cnt2 = pre[i] + suf[1+2].size();
            ans = max(ans, cnt2);

            // update suffix
            cnt[pos]--;
            for(int j=0; j<5; j++){         // build suffix to check the current position whether will be hit by offset
                int p = pos-2+j;
                if(target[p+100000] && cnt[p] == 0) suf[j].insert(p);
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}


/*
2 4
-1 0
FFRF
(2)

2 4
-1 0
FFLF
(2)

2 4
-1 0
FFRR
(1)

3 6
-1 0 1
LLFFRR
(2)

7 7
-3 -2 -1 0 1 2 3
FLFLFFF

*/
