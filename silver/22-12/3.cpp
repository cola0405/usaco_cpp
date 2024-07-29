// math
// assume a[0]=0, we can use a[i] +- r[i][i+1] to get a[1] and so on
// so the keypoint of this problem is to check the validation
// the time complexity of dfs is O(n^2) not the good solution

// proof of feasibility of a[0]=0
// as we know 0 <= ai <= 10^9, -10^9 <= bi <= 10^9
// so we set the a[0] = 0 is absolutely no problem even with the offset

// only need to detect r(0,i), r(1,i), ... , r(i-1,i)
// you may consider -- what about previous rules like: r(i,i+1), r(i,i+2),...
// let's see a[i+1], it's comes from a[i] + r, it's affected by a[i] and rule, so it's must fit the r rule
// in other words, if a[i] go really large, a[i+1], a[i+2], .. are also affected
// so we don't need to check the following rules
// but we need to check the previous rules
// because the previous numbers are not affected by a[i]

#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

const int N=300, M=1e9;
ll n;
ll r[N+1][N+1];
ll mn[N+1][N+1], mx[N+1][N+1];
ll a[N+1];

void update_mn_mx(int i){
    for(int j=0; j<n; j++){
        for(int k=0; k<n; k++){
            if(j<=i && i<=k){
                mn[j][k] = min(mn[j][k], a[i]);
                mx[j][k] = max(mx[j][k], a[i]);
            }
        }
    }
}

int main()
{
    // freopen("3.in", "r", stdin);
    // freopen("3.out", "w", stdout);

    cin>>n;
    for(int i=0; i<n; i++){
        for(int j=i; j<n; j++){
            cin>>r[i][j];
        }
    }
    // assume start from 0 (bi should be in range(-1e9, 1e9), so don't worry)
    a[0] = 0;   

    // reset mn and mx
    for(int i=0; i<n; i++){
        for(int j=i; j<n; j++){
            if(i == 0) {
                mn[i][j] = 0;       // relative with a[0]
                mx[i][j] = 0;
            }
            else{
                mn[i][j] = 2e9;
                mx[i][j] = -2e9;
            }
        }
    }
    
    // fill the array
    for(int i=0; i<n-1; i++){
        // try positive
        a[i+1] = a[i] + r[i][i+1];
        int flag = true;
        for(int j=0; j<=i; j++){
            // update mn and mx later (no need to do the backtracking)
            if(max(mx[j][i+1], a[i+1]) - min(mn[j][i+1], a[i+1]) != r[j][i+1]) flag = false;
        }
        // set negative, no need to check again, because it's guaranteed there do have the valid answer
        if(flag == false){
            a[i+1] = a[i] - r[i][i+1];
        }
        update_mn_mx(i+1);
    }
    for(int i=0; i<n; i++) {cout << a[i]; if(i!=n-1) cout << ' ';}
    return 0;
}
