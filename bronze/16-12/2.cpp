#include <iostream>
#include <unordered_map>
using namespace std;

unordered_map<char,int> count(){
    string a,b;
    cin>>a>>b;
    unordered_map<char,int> cnt1, cnt2;
    for(auto c: a) cnt1[c]++;
    for(auto c: b) cnt2[c]++;
    for(auto &[c, cnt] : cnt2){
        cnt1[c] = max(cnt1[c], cnt2[c]);
    }
    return cnt1;        // count the maximal demand of the letters from two words
}

int main()
{
    freopen("blocks.in", "r", stdin);
    freopen("blocks.out", "w", stdout);

    int n;
    cin>>n;
    unordered_map<char,int> ans;
    for(int i=0; i<n; i++){
        auto d = count();
        for(auto &[c,cnt] : d) ans[c] += cnt;
    }
    for(int i=0; i<26; i++){
        cout<<ans[char('a'+i)]<<endl;
    }
    return 0;
}
