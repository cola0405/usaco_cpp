// 2D array + sort + topological

// because the meet only happen between N and E
// so we can divide points into two groups
// sort them to sovle the topological problem

// this algorithm treat 2D array like this:
// ------> (y, N)
// |
// |
// v (x, E)

// sort the e by y, sort the n by x
// for(int i=0; i<e.size(); i++)
//     for(int j=0; j<n.size(); j++)
// for the cow-e（who face the east）, we start from the most left one -- smallest y
// because the cow-n really care about whether there do have cow be stopped by it before
// and the cow-e is the same, it also care about the topper cow-n

// so sort e and n, and check them in order can sovle the topologic problem 
// (always check the cow in order to avoid missing)


#include <bits/stdc++.h>
using namespace std;

struct point{
    int x,y,id;
};

int m;
vector<point> e,n;

bool cmp_x(point& a, point& b){
    return a.x < b.x;
}
bool cmp_y(point& a, point& b){
    return a.y < b.y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("3.in", "r", stdin);

    cin>>m;
    for(int i=0; i<m; i++){
        int x,y;
        char d;
        cin>>d>>x>>y;
        if(d == 'E') e.push_back({x,y,i});
        else n.push_back({x,y,i});
    }

    sort(n.begin(), n.end(), cmp_x);
    sort(e.begin(), e.end(), cmp_y);

    vector<int> stop(m, 0), ans(m, 0);
    for(int i=0; i<e.size(); i++){
        for(int j=0; j<n.size(); j++){
            if(stop[n[j].id] || n[j].x < e[i].x || n[j].y > e[i].y) continue;
            // point j is on the left bottom of i
            if(n[j].x - e[i].x < e[i].y - n[j].y){
                ans[e[i].id] += ans[n[j].id] + 1;
                stop[n[j].id] = 1;
            }
            else if(n[j].x - e[i].x > e[i].y - n[j].y){
                ans[n[j].id] += ans[e[i].id] + 1;
                stop[e[i].id] = 1;
                break;
            }
        }
    }
    for(auto x: ans) cout<<x<<endl;
    return 0;
}