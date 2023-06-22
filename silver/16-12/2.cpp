#include <bits/stdc++.h>
using namespace std;

int main(){
    freopen("citystate.in", "r", stdin);
    freopen("citystate.out", "w", stdout);

    int n;
    cin>>n;
    unordered_map<string, unordered_map<string, int>> c2s;
    vector<vector<string>> record;
    int ans = 0;
    for(int i=0; i<n; i++){
        string city, state;
        cin>>city>>state;
        city = city.substr(0,2);
        c2s[city][state]++;
        record.push_back({city, state});
    }

    for(auto & item : record){
        string city = item[0];
        string state = item[1];
        if(city == state)continue;  // 必须来自不同州，那city和state相同的就不用看了
        ans += c2s[state][city];
    }
    cout<<ans/2<<endl;
    return 0;
}