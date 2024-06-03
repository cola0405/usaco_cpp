// game theory + greedy + suffix
#include <bits/stdc++.h>
using namespace std;

int EVEN = 0, ODD = 1;
vector<string> d = {"Even", "Odd"};

void solve(){
    vector<vector<int>> changes;
    vector<int> worst_future;   // the marbles we can got in the worst situation
    int marble;
    int n,m,k;
    cin>>n>>m>>k;
    for(int v=0; v<m; v++){
        vector<int> guess = {INT_MAX, INT_MAX};
        for(int g=0; g<k; g++){     // when it has the mixed parity, we can't win
            cin>>marble;
            int parity = marble%2;      // the actual parity
            // record the worst situation when choosing EVEN or ODD
            guess[parity] = min(guess[parity], marble);       // for actual parity, we guess right, so it's +marble
            guess[parity^1] = min(guess[parity^1], -marble);  // incorrect, -marble
        }
        changes.push_back(guess);
    }
    worst_future.resize(m+1);
    for(int i=m-1; i>=0; i--){
        // may lose
        worst_future[i] = min(0, max(changes[i][0], changes[i][1]) + worst_future[i+1]);
    }
    if(n + worst_future[0] <= 0){
        cout<<-1<<endl;
        return;
    }
    // greedy + suffix to confirm the choice
    vector<int> ans;
    int cur = n;
    for(int i=0; i<m; i++){
        int p;
         // if choose even can win in the end
        if(cur + changes[i][EVEN] + worst_future[i+1] > 0) p = EVEN;
        else p = ODD;
        cur += changes[i][p];
        ans.push_back(p);
    }

    for(int i=0; i<m-1; i++) cout<<d[ans[i]]<<' ';
    cout<<d[ans.back()]<<endl;
}

int main(){
    // freopen("3.in", "r", stdin);
    // freopen("3.out", "w", stdout);

    int T;
    cin>>T;
    for(int u=0; u<T; u++){
        solve();
    }
}