#include <iostream>
#include <vector>
using namespace std;

int main()
{
    freopen("lifeguards.in", "r", stdin);
    freopen("lifeguards.out", "w", stdout);

    int n,total=0;
    cin>>n;
    vector<pair<int,int>> lg(n);        // lifeguard
    vector<int> t(1000, 0);
    for(int i=0; i<n; i++){
        cin>>lg[i].first>>lg[i].second;
        for(int j=lg[i].first; j<lg[i].second; j++){
            if(t[j] == 0) total++;      // calculate the covered area
            t[j]++;
        }
    }
    int min_cnt = 1e9;
    for(auto &[a,b] : lg){            // try to fire each lifeguard
        int cnt = 0;                
        for(int i=a; i<b; i++){
            if(t[i] == 1) cnt++;      // count the unique moment
        }
        min_cnt = min(min_cnt, cnt);  // get the minimal lost
    }
    cout<<total-min_cnt<<endl;
    return 0;
}
