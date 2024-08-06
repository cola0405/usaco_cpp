// geometry

// parallel to axis, so we can put the points in a map
// X[x] = {y1,y2,y3} store the all y values of points with the same x -- parallel with y axis
// Y[y] -- parallel with x axis

// then we can take every point as the apex
// if we try all pairs of points, it's O(n^3), not working
// let's check out the formula

// assume dx1 is the x distance between p1 and apex
// we will know we need to add dx1*dy1 + dx1*dy2 + ... + dx2*dy1 + dx2*dy2
// we can find for all dx and dy, it's all matched with the nested loop
// we can quickly calculate this with sum(dx) * sum(dy)

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
unordered_map<int,vector<int>> X,Y;
vector<pair<int,int>> points;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);

    cin>>n;
    for(int i=0; i<n; i++){
        int x,y;
        cin>>x>>y;
        X[x].push_back(y);
        Y[y].push_back(x);
        points.push_back({x,y});
    }
    long long ans = 0;
    for(auto &[x,y] : points){
        ll dx=0, dy=0;          // 10^4 - (-10^4) = 2x10^4, sum of them may cause int overflow
        for(auto &y1 : X[x]) dy += abs(y1-y);
        for(auto &x1 : Y[y]) dx += abs(x1-x);
        ans += dx*dy;
        ans %= 1000000007;
    }
    cout<<ans<<endl;
    return 0;
}