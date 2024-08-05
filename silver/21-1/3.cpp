// 2D-array + restriction help

// for each column, we can only choose odd or even numbers in that column
// 奇偶偶奇      偶偶奇奇
// *CC*         CC**  
// C**C         **CC
// *CC*         CC**
// C**C         **CC

// the same rule also fit for each row
// 奇 *C*C       偶 C*C*  
// 偶 C**C       偶 C*C*
// 奇 *C*C       偶 C*C*
// 偶 C*C*       奇 *C*C

// for each colum, we try to pick up the max(odd, even) -- add together we got ans1
// for each row, we try to pick up the max(odd, even)  -- add together we got ans2
// ans = max(ans1, ans2)

#include <bits/stdc++.h>
using namespace std;

const int N = 1000;
int n;
int a[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("3.in", "r", stdin);

    cin>>n;
    vector<int> odd1(n, 0), even1(n, 0), odd2(n, 0), even2(n, 0);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin>>a[i][j];
            if(i%2 == 0) even1[j] += a[i][j];
            else odd1[j] += a[i][j];
            if(j%2 == 0) even2[i] += a[i][j];
            else odd2[i] += a[i][j];
        }
    }
    int ans1 = 0, ans2 = 0;
    for(int i=0; i<n; i++){
        ans1 += max(odd1[i], even1[i]);
        ans2 += max(odd2[i], even2[i]);
    }
    cout<<max(ans1, ans2)<<endl;
    return 0;
}