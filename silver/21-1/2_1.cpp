// optimiazation

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

    // build prefix
    vector<int> pre = {0};
    vector<int> flag(26, 0);    // the status of each color, long stroke is avaliable or not
    for(int i=0; i<n; i++){
        if(flag[s[i]-65]) pre.push_back(pre.back());    // long stroke is still available
        else{
            pre.push_back(pre.back() + 1);
            flag[s[i]-65] = 1;
        }
        for(int j=s[i]-65 + 1; j<26; j++) flag[j] = 0;  // set the darker color to be unavailable when we meet s[i]
    }

    // build suffix
    vector<int> suf = {0};
    fill(flag.begin(), flag.end(), 0);
    for(int i=n-1; i>=0; i--){
        if(flag[s[i]-65]) suf.push_back(suf.back());    // long stroke is still available
        else{
            suf.push_back(suf.back() + 1);
            flag[s[i]-65] = 1;
        }
        for(int j=s[i]-65 + 1; j<26; j++) flag[j] = 0;
    }

    for(int i=0; i<q; i++){
        int a,b;
        cin>>a>>b;
        cout<<pre[a-1] + suf[n-b]<<'\n';
    }
    return 0;
}