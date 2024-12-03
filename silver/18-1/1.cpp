// 把每对点拆出来 sort
// 需要统计总覆盖区间 sum 和 最小独占区间 min_own
// ans = sum - min_own

// 总覆盖区间统计方法：只要左边有 start 还没有被配对，就可以进行统计
// 最小独占区间统计方法：如果左边只有一个start，那么就可以进行统计

#include <bits/stdc++.h>
using namespace std;

int main(){
    freopen("lifeguards.in", "r", stdin);
    freopen("lifeguards.out", "w", stdout);

    int n, start, end, sum = 0, last = 0;
    vector<vector<int>> points;
    unordered_set<int> left;          // id of the start
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>start>>end;
        points.push_back({start, i});
        points.push_back({end, i});
    }
    sort(points.begin(), points.end());

    vector<int> own(n);
    for(int i=0; i<2*n; i++){
        int pos = points[i][0];
        int cur_id = points[i][1];

        int gap = pos - last;
        if(left.size() == 1){           // 只有左边只有一个start的时候，才可以统计当前的独占区间
            for(int id : left) own[id] += gap;
        }
        if(left.size() > 0) sum += gap;  // 如果有左端点存在，则可以统计有效覆盖区间

        // 再次找到 cur_id，说明当前点是 end， 需要删除 left 中对应的start
        if(left.find(cur_id) != left.end()) left.erase(cur_id);
        else left.insert(cur_id);
        last = pos;
    }
    cout<< sum - (*min_element(own.begin(), own.end())) <<endl;
    return 0;
}