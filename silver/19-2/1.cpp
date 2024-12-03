// https://usaco.org/index.php?page=viewproblem2&cpid=918

// sliding window
// try testcase: 1 5 13 15
// for max: the key point is still using empty space -- try to moves all cows to the left or right
// the empty space is the max number of operations
// for min: in the end, the n cows must be in a window, which size is exactly n
// so we just need to find out which window has the most cows in the beginning

#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a;
int get_min(){
    // right side with n-1 contiguous cows
    // 1 5 6 7
    if(a[1]-a[0] > 2 && a[n-1]-a[1]+1 == n-1) return 2;        // right side
    if(a[n-1]-a[n-2] > 2 && a[n-2]-a[0]+1 == n-1) return 2;    // left side

    int max_cow = 0;
    for(int i = 0; i < n; i++){
        int j = i;
        // can't use nested loop to check, which will reach O(n^2)
        while(j < n && a[j] < a[i] + n) j++;
        max_cow = max(max_cow, j-i);
    }
    return n - max_cow;         // just move the outside cows into the windows 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("herding.in", "r", stdin);
    freopen("herding.out", "w", stdout);

    cin >> n;
    a = vector<int>(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());

    int min_op = get_min();
    int max_op = max(a[n-1] - a[1], a[n-2] - a[0]) - (n-2);     //  n-2, substract the two endpoints (a[n-1], a[1]), (a[n-2], a[0])
    cout << min_op << '\n' << max_op << endl;
    return 0;
}