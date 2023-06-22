#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("bcount.in", "r", stdin);
    freopen("bcount.out", "w", stdout);

    int n,q;
    cin>>n>>q;

    // init 3 prefix sum
    vector<vector<int>> p(4, vector<int>(n+1));
    for(int i=1; i<=n; i++){
        for(int j=1; j<=3; j++){
            p[j][i] = p[j][i-1];
        }
        int cow;
        cin>>cow;
        p[cow][i] += 1;
    }

    // get interval from prefix sum
    for(int i=0; i<q; i++){
        int left, right;
        cin>>left>>right;

        int H = p[1][right] - p[1][left-1];
        int G = p[2][right] - p[2][left-1];
        int J = p[3][right] - p[3][left-1];

        cout<<H<<" "<<G<<" "<<J<<endl;
    }
    return 0;
}