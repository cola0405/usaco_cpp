#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("hps.in","r",stdin);
    freopen("hps.out","w",stdout);

    int n;
    cin>>n;
    unordered_map<string, vector<int>> count = {{"P",{0}},{"H",{0}},{"S",{0}}};
    for(int i=0; i<n; i++){
        string c;
        cin>>c;
        count["P"].push_back(count["P"][i]);
        count["H"].push_back(count["H"][i]);
        count["S"].push_back(count["S"][i]);
        count[c][i+1]++;
    }

    vector<string> p = {"P", "H", "S"};
    unordered_map<string, string> win = {{"H","S"}, {"S","P"}, {"P","H"}};
    int ans = 0;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(i==j)continue;
            string left=p[i], right=p[j];
            for(int k=1; k<=n; k++){
                // 在k切换手势
                int score = 0;
                score += count[win[left]][k-1];  // 第一个手势
                score += count[win[right]][n] - count[win[right]][k-1];  // 第二个手势
                ans = max(score, ans);
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}