// python 暴力只能过5个, c++能过9个
#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("div7.in", "r", stdin);
    freopen("div7.out", "w", stdout);

    int n;
    cin>>n;

    // init prefix sum
    vector<long long> p(n+1,0);
    for(int i=1; i<=n; i++){
        int id;
        cin>>id;
        p[i] = p[i-1]+id;
    }

    int ans = 0;
    for(int i=1; i<=n; i++){
        for(int j=n; j>=i+ans; j--){
            long long s = p[j]-p[i-1];
            if(s%7==0){
                ans = j-i+1;
                break;
            }
        }
    }

    cout<<ans<<endl;
    return 0;
}

